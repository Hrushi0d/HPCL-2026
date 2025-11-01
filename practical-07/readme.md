## Assigment - 06

Press Start and open “x64 Native Tools Command Prompt for VS 2022” (cmd.exe)
or “Developer PowerShell for VS 2022”.

Statement - 1
```bash
cl ".\practical-07\practical-07-1.c" /I "C:\Program Files (x86)\Microsoft SDKs\MPI\Include" /Fo".\practical-07\practical-07-1.obj" /Fe".\practical-07\practical-07-1.exe" /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib
mpiexec -n 4 .\practical-07\practical-07-1.exe 
mpiexec -n 6 .\practical-07\practical-07-1.exe 
mpiexec -n 6 .\practical-07\practical-07-1.exe 
```
Statement - 2
```bash
cl ".\practical-07\practical-07-2.c" /I "C:\Program Files (x86)\Microsoft SDKs\MPI\Include" /Fo".\practical-07\practical-07-2.obj" /Fe".\practical-07\practical-07-2.exe" /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib
mpiexec -n 4 .\practical-07\practical-07-2.exe 
mpiexec -n 6 .\practical-07\practical-07-2.exe 
mpiexec -n 6 .\practical-07\practical-07-2.exe 
```