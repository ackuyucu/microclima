#include <Rcpp.h>
using namespace Rcpp;
//' invls_calc
//'
//' This function returns a numeric matrix identifying
//' matching values from a raster that intersect with
//' a set of points
//' @export
// [[Rcpp::export]]
NumericMatrix invls_calc(NumericMatrix lsm, double resolution,
                   double xmin, double ymax, NumericVector s,
                   int direction, NumericMatrix slr,
                   double slr_xmin, double slr_xmax,
                   double slr_ymin, double slr_ymax){

  double pi = 3.141593;
  int lsm_row = lsm.nrow();
  int lsm_col = lsm.ncol();

  //set up collection matrix
  NumericMatrix lsw(lsm_row,lsm_col);

  //for each cell in the land/sea mask
  for(int yy = 0; yy < lsm_row; ++yy) {
    for(int xx = 0; xx < lsm_col; ++xx) {
	  
	  //if it is not a sea pixel...
      if (lsm(yy,xx) != 0) {

        double x = (xx + 1) * resolution + xmin - resolution / 2;
        double y = ymax + resolution / 2 - (yy + 1) * resolution;

        NumericVector xdist = round(s * sin(direction * pi / 180), 0);
        NumericVector ydist = round(s * cos(direction * pi / 180), 0);

        //update existing
        xdist = xdist + x;
        ydist = ydist + y;

        //create matrix of xy coords (points)
        NumericMatrix xy(xdist.size(),2);
        xy(_,0) = xdist;
        xy(_,1) = ydist;

        //collector
        NumericVector lsc(xy.nrow());

        //for every point (in steps away from focal cell)
        for (int point = 0; point < xy.nrow(); point++) {
          double x2 = xy(point,0);
          double y2 = xy(point,1);

          //check position of point falls within raster
          if (x2 > slr_xmin && slr_xmax > x2 && y2 > slr_ymin && slr_ymax > y2) {
			
			//work out index of position
            double rdist = slr_ymax - y2;
            int row = floor(rdist/resolution);
            double cdist = x2 - slr_xmin;
            int col = floor(cdist/resolution);

            //pull value from slr that matches the point
            lsc(point) = slr(row, col);
          } else {
            //if no point matches add NA to collector
            lsc(point) = NA_REAL;
          }
        }

        lsc(0) = 1;
        lsc = na_omit(lsc);

        if(lsc.size() > 0) {

          lsw(yy,xx) = sum(lsc) / lsc.size();

        } else {

          lsw(yy,xx) = 1;

        }

      } else {
        lsw(yy,xx) = NA_REAL;
        }
      }
    }
  return lsw;
}