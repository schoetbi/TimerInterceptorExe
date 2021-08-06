# TimerInterceptorExe
Windows application to forward command line arguments to real application to measure the execution time

## Why?

I wrote this application because I needed a way to measure the time of all invocations of a windows application. This application generates a log file that contains
the measured runtimes for each call of the application.

## Usage

At the moment this is only usable for windows applications. To use this the following example is used. Say there is an application called `timeburner.exe`. Before 
measurement there are several steps needed:

1. Rename `timeburner.exe` to `timeburner_real.exe`
2. Copy `TimeInterceptor.exe` in the same directory as `timeburner_real.exe`
3. Rename `TimeInterceptor.exe` to `timeburner.exe`

As soon as someone tries to exeute timeburner.exe the measurement exeutable gets executed and starts the __real__ process timeburner_real.exe and 
measures the time in milliseconds. The result is stored in a log file called `timeburner.log`

Log file
```
2021/07/06 08:28:31	2974	ms	 Arguments
2021/07/06 08:28:34	1978	ms	 Arguments
2021/07/06 08:28:40	2904	ms	 Arguments
2021/07/06 08:28:46	1692	ms	 Arguments
2021/07/06 08:28:49	1646	ms	 Arguments
2021/07/06 08:28:49	1645	ms	 Arguments
2021/07/06 08:28:50	1668	ms	 Arguments
2021/07/06 08:28:55	1056	ms	 Arguments
2021/07/06 08:28:58	1628	ms	 Arguments
2021/07/06 08:28:58	1592	ms	 Arguments
2021/07/06 08:28:59	1427	ms	 Arguments
2021/07/06 08:29:01	1502	ms	 Arguments
2021/07/06 08:29:02	1686	ms	 Arguments
2021/07/06 08:29:05	1939	ms	 Arguments
```
