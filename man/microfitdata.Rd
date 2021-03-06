% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/data.R
\docType{data}
\name{microfitdata}
\alias{microfitdata}
\title{May 2010 Data for fitting microclimate model.}
\format{A data frame with 11761 rows and 5 variables:
\describe{
\item{obs_time}{The time of the logger recording, in DD/MM/YY HH:MM:SS format}
\item{temperature}{The mean hourly logger temperature reading (ºC)}
\item{reftemp}{The predicted reference temperature at the logger location as output by the mesoclimate model (ºC)}
\item{wind}{The predicted wind speed at the logger locations (\ifelse{html}{\out{m s<sup>-1</sup> }}{\eqn{m s^{-1}}})}
\item{netrad}{The predicted net radiation at the logger locations (\ifelse{html}{\out{MJ m<sup>-2</sup> hr<sup>-1</sup>}}{\eqn{MJ m^{-2} hr^{-1}}})}
}}
\usage{
microfitdata
}
\description{
A dataset containing the hourly temperature logger data and net
radiation and wind data at each logger location  in May 2010.
}
\keyword{datasets}
