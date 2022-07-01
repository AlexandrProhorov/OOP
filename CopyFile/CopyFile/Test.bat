set PROGRAM= "%~1"

set OUT= "%TEMP%\out.txt"


echo first test - normal text
%PROGRAM%  In.txt  %OUT% || goto err
fc.exe %OUT% Copy-out.txt || goto err

echo second test - empty file
%PROGRAM%  EmptyIn.txt  %OUT% || goto err
fc.exe %OUT% EmptyCopy-out.txt || goto err

echo third test - file with numbers
%PROGRAM%  NumberIn.txt  %OUT% || goto err
fc.exe %OUT% NumberCopy-out.txt || goto err




echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1