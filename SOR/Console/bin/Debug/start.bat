@echo off
for /l %%i in (3,1,9) do (
	for /l %%j in (0,1,2) do (
		if exist C:/SOR/Tests/Results/ans%%i_%%j (
			call Console C:/SOR/Tests/test%%i.1.txt C:/SOR/Tests/test%%i.2.txt %%j C:/SOR/Tests/ans%%i_%%j.txt C:/SOR/Tests/Results/ans%%i_%%j
		) else (
			call Console C:/SOR/Tests/test%%i.1.txt C:/SOR/Tests/test%%i.2.txt %%j C:/SOR/Tests/ans%%i_%%j.txt
		)
	)
)
pause