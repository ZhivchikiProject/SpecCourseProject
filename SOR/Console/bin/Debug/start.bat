@echo off
for /l %%i in (3,1,9) do (
	for /l %%j in (0,1,2) do (
		if exist C:/SOR/Tests/Results/ans%%i_%%j (
			call Console ../../../Tests/test%%i.1.txt ../../../Tests/test%%i.2.txt %%j ../../../Tests/ans%%i_%%j.txt ../../../Tests/Results/ans%%i_%%j
		) else (
			call Console ../../../Tests/test%%i.1.txt ../../../Tests/test%%i.2.txt %%j ../../../Tests/ans%%i_%%j.txt
		)
	)
)
pause