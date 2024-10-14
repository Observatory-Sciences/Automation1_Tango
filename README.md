Compilation instruction on conda: 
1) Create environment for Tango 9.5:

`conda create -n automation1 -c conda-forge cpptango=9.5 cppzmq omniorb 
  pkg-config pogo make`
 
2) Activate environment: 

`conda activate automation1`

3) Export environment variables:

   `export TANGO_HOME=$CONDA_PREFIX`

4) If you have local copy of Automation1 Library and Headers:
   
   `export A1LIB_HOME=<path>`

   `export A1HEADER_HOME=<path>`
