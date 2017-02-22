cmake_minimum_required(VERSION 3.6)
project(parsnp)

set(CMAKE_C_COMPILER "/usr/local/Cellar/gcc@4.9/4.9.3_1/bin/gcc-4.9")
set(CMAKE_CXX_COMPILER "/usr/local/Cellar/gcc@4.9/4.9.3_1/bin/c++-4.9")


set(OpenMP_C_FLAG_CANDIDATES
        #Gnu
        "-fopenmp"
        #Microsoft Visual Studio
        "/openmp"
        #Intel windows
        "-Qopenmp"
        #Intel
        "-openmp"
        #Empty, if compiler automatically accepts openmp
        " "
        #Sun
        "-xopenmp"
        #HP
        "+Oopenmp"
        #IBM XL C/c++
        "-qsmp"
        #Portland Group
        "-mp"
        )
set(OpenMP_CXX_FLAG_CANDIDATES ${OpenMP_C_FLAG_CANDIDATES})

# sample openmp source code to test
set(OpenMP_C_TEST_SOURCE
        "
#include <omp.h>
int main() {
#ifdef _OPENMP
  return 0;
#else
  breaks_on_purpose
#endif
}
")
# use the same source for CXX as C for now
set(OpenMP_CXX_TEST_SOURCE ${OpenMP_C_TEST_SOURCE})
# if these are set then do not try to find them again,
# by avoiding any try_compiles for the flags
if(DEFINED OpenMP_C_FLAGS AND DEFINED OpenMP_CXX_FLAGS)
    set(OpenMP_C_FLAG_CANDIDATES)
    set(OpenMP_CXX_FLAG_CANDIDATES)
endif(DEFINED OpenMP_C_FLAGS AND DEFINED OpenMP_CXX_FLAGS)

# check c compiler
foreach(FLAG ${OpenMP_C_FLAG_CANDIDATES})
    set(SAFE_CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS}")
    set(CMAKE_REQUIRED_FLAGS "${FLAG}")
    #unset(OpenMP_FLAG_DETECTED CACHE)
    message(STATUS "Try OpenMP C flag = [${FLAG}]")
    check_c_source_compiles("${OpenMP_CXX_TEST_SOURCE}" OpenMP_FLAG_DETECTED)
    set(CMAKE_REQUIRED_FLAGS "${SAFE_CMAKE_REQUIRED_FLAGS}")
    if(OpenMP_FLAG_DETECTED)
        set(OpenMP_C_FLAGS_INTERNAL "${FLAG}")
        break()
    endif(OpenMP_FLAG_DETECTED)
endforeach(FLAG ${OpenMP_C_FLAG_CANDIDATES})

# check cxx compiler
foreach(FLAG ${OpenMP_CXX_FLAG_CANDIDATES})
    set(SAFE_CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS}")
    set(CMAKE_REQUIRED_FLAGS "${FLAG}")
    #unset(OpenMP_FLAG_DETECTED CACHE)
    message(STATUS "Try OpenMP CXX flag = [${FLAG}]")
    check_cxx_source_compiles("${OpenMP_C_TEST_SOURCE}" OpenMP_FLAG_DETECTED)
    set(CMAKE_REQUIRED_FLAGS "${SAFE_CMAKE_REQUIRED_FLAGS}")
    if(OpenMP_FLAG_DETECTED)
        set(OpenMP_CXX_FLAGS_INTERNAL "${FLAG}")
        break()
    endif(OpenMP_FLAG_DETECTED)
endforeach(FLAG ${OpenMP_CXX_FLAG_CANDIDATES})

set(OpenMP_C_FLAGS "${OpenMP_C_FLAGS_INTERNAL}"
        CACHE STRING "C compiler flags for OpenMP parallization")

set(OpenMP_CXX_FLAGS "${OpenMP_CXX_FLAGS_INTERNAL}"
        CACHE STRING "C++ compiler flags for OpenMP parallization")
# handle the standard arguments for find_package
#find_package_handle_standard_args(OpenMP DEFAULT_MSG
 #       OpenMP_C_FLAGS OpenMP_CXX_FLAGS )

set(OpenMP_C_FLAGS "-fopenmp")
set(OpenMP_CXX_FLAGS "-fopenmp")
include(FindOpenMP)

IF(OPENMP_FOUND)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
ENDIF()




set(SOURCE_FILES
        muscle/libMUSCLE/aligngivenpath.cpp
        muscle/libMUSCLE/aligngivenpathsw.cpp
        muscle/libMUSCLE/aligntwomsas.cpp
        muscle/libMUSCLE/aligntwoprofs.cpp
        muscle/libMUSCLE/aln.cpp
        muscle/libMUSCLE/alpha.cpp
        muscle/libMUSCLE/alpha.h
        muscle/libMUSCLE/anchoredpp.cpp
        muscle/libMUSCLE/anchors.cpp
        muscle/libMUSCLE/bittraceback.cpp
        muscle/libMUSCLE/blosum62.cpp
        muscle/libMUSCLE/blosumla.cpp
        muscle/libMUSCLE/clust.cpp
        muscle/libMUSCLE/clust.h
        muscle/libMUSCLE/cluster.cpp
        muscle/libMUSCLE/cluster.h
        muscle/libMUSCLE/clustset.h
        muscle/libMUSCLE/clustsetdf.h
        muscle/libMUSCLE/clustsetmsa.h
        muscle/libMUSCLE/clwwt.cpp
        muscle/libMUSCLE/color.cpp
        muscle/libMUSCLE/cons.cpp
        muscle/libMUSCLE/diaglist.cpp
        muscle/libMUSCLE/diaglist.h
        muscle/libMUSCLE/diffobjscore.cpp
        muscle/libMUSCLE/diffpaths.cpp
        muscle/libMUSCLE/difftrees.cpp
        muscle/libMUSCLE/difftreese.cpp
        muscle/libMUSCLE/distcalc.cpp
        muscle/libMUSCLE/distcalc.h
        muscle/libMUSCLE/distfunc.cpp
        muscle/libMUSCLE/distfunc.h
        muscle/libMUSCLE/distpwkimura.cpp
        muscle/libMUSCLE/domuscle.cpp
        muscle/libMUSCLE/dosp.cpp
        muscle/libMUSCLE/dpregionlist.h
        muscle/libMUSCLE/dpreglist.cpp
        muscle/libMUSCLE/dpreglist.h
        muscle/libMUSCLE/drawtree.cpp
        muscle/libMUSCLE/edgelist.cpp
        muscle/libMUSCLE/edgelist.h
        muscle/libMUSCLE/enumopts.cpp
        muscle/libMUSCLE/enumopts.h
        muscle/libMUSCLE/enums.h
        muscle/libMUSCLE/enumtostr.cpp
        muscle/libMUSCLE/estring.cpp
        muscle/libMUSCLE/estring.h
        muscle/libMUSCLE/fasta.cpp
        muscle/libMUSCLE/fasta2.cpp
        muscle/libMUSCLE/fastclust.cpp
        muscle/libMUSCLE/fastdist.cpp
        muscle/libMUSCLE/fastdistjones.cpp
        muscle/libMUSCLE/fastdistkbit.cpp
        muscle/libMUSCLE/fastdistkmer.cpp
        muscle/libMUSCLE/fastdistmafft.cpp
        muscle/libMUSCLE/fastdistnuc.cpp
        muscle/libMUSCLE/fastscorepath2.cpp
        muscle/libMUSCLE/finddiags.cpp
        muscle/libMUSCLE/finddiagsn.cpp
        muscle/libMUSCLE/gapscoredimer.h
        muscle/libMUSCLE/glbalign.cpp
        muscle/libMUSCLE/glbalign352.cpp
        muscle/libMUSCLE/glbaligndiag.cpp
        muscle/libMUSCLE/glbalignle.cpp
        muscle/libMUSCLE/glbalignsimple.cpp
        muscle/libMUSCLE/glbalignsp.cpp
        muscle/libMUSCLE/glbalignspn.cpp
        muscle/libMUSCLE/glbalignss.cpp
        muscle/libMUSCLE/glbalndimer.cpp
        muscle/libMUSCLE/globals.cpp
        muscle/libMUSCLE/globalslinux.cpp
        muscle/libMUSCLE/globalsother.cpp
        muscle/libMUSCLE/globalswin32.cpp
        muscle/libMUSCLE/gonnet.cpp
        muscle/libMUSCLE/gonnet.h
        muscle/libMUSCLE/gotowt.cpp
        muscle/libMUSCLE/henikoffweight.cpp
        muscle/libMUSCLE/henikoffweightpb.cpp
        muscle/libMUSCLE/html.cpp
        muscle/libMUSCLE/hydro.cpp
        muscle/libMUSCLE/intmath.cpp
        muscle/libMUSCLE/intmath.h
        muscle/libMUSCLE/local.cpp
        muscle/libMUSCLE/main.cpp
        muscle/libMUSCLE/makerootmsa.cpp
        muscle/libMUSCLE/makerootmsab.cpp
        muscle/libMUSCLE/maketree.cpp
        muscle/libMUSCLE/mhack.cpp
        muscle/libMUSCLE/mpam200.cpp
        muscle/libMUSCLE/msa.cpp
        muscle/libMUSCLE/msa.h
        muscle/libMUSCLE/msa2.cpp
        muscle/libMUSCLE/msadist.h
        muscle/libMUSCLE/msadistkimura.cpp
        muscle/libMUSCLE/msf.cpp
        muscle/libMUSCLE/muscle.cpp
        muscle/libMUSCLE/muscle.h
        muscle/libMUSCLE/muscleout.cpp
        muscle/libMUSCLE/nucmx.cpp
        muscle/libMUSCLE/nwdasimple.cpp
        muscle/libMUSCLE/nwdasimple2.cpp
        muscle/libMUSCLE/nwdasmall.cpp
        muscle/libMUSCLE/nwrec.cpp
        muscle/libMUSCLE/nwsmall.cpp
        muscle/libMUSCLE/objscore.cpp
        muscle/libMUSCLE/objscore.h
        muscle/libMUSCLE/objscore2.cpp
        muscle/libMUSCLE/objscoreda.cpp
        muscle/libMUSCLE/onexception.cpp
        muscle/libMUSCLE/options.cpp
        muscle/libMUSCLE/outweights.cpp
        muscle/libMUSCLE/pam200mafft.cpp
        muscle/libMUSCLE/params.cpp
        muscle/libMUSCLE/params.h
        muscle/libMUSCLE/phy.cpp
        muscle/libMUSCLE/phy2.cpp
        muscle/libMUSCLE/phy3.cpp
        muscle/libMUSCLE/phy4.cpp
        muscle/libMUSCLE/phyfromclust.cpp
        muscle/libMUSCLE/phyfromfile.cpp
        muscle/libMUSCLE/physeq.cpp
        muscle/libMUSCLE/phytofile.cpp
        muscle/libMUSCLE/posgap.cpp
        muscle/libMUSCLE/ppscore.cpp
        muscle/libMUSCLE/profdb.cpp
        muscle/libMUSCLE/profile.cpp
        muscle/libMUSCLE/profile.h
        muscle/libMUSCLE/profilefrommsa.cpp
        muscle/libMUSCLE/progalign.cpp
        muscle/libMUSCLE/progress.cpp
        muscle/libMUSCLE/progressivealign.cpp
        muscle/libMUSCLE/pwpath.cpp
        muscle/libMUSCLE/pwpath.h
        muscle/libMUSCLE/readmx.cpp
        muscle/libMUSCLE/realigndiffs.cpp
        muscle/libMUSCLE/realigndiffse.cpp
        muscle/libMUSCLE/refine.cpp
        muscle/libMUSCLE/refine.h
        muscle/libMUSCLE/refinehoriz.cpp
        muscle/libMUSCLE/refinesubfams.cpp
        muscle/libMUSCLE/refinetree.cpp
        muscle/libMUSCLE/refinetreee.cpp
        muscle/libMUSCLE/refinevert.cpp
        muscle/libMUSCLE/refinew.cpp
        muscle/libMUSCLE/savebest.cpp
        muscle/libMUSCLE/scoredist.cpp
        muscle/libMUSCLE/scoregaps.cpp
        muscle/libMUSCLE/scorehistory.cpp
        muscle/libMUSCLE/scorehistory.h
        muscle/libMUSCLE/scorepp.cpp
        muscle/libMUSCLE/seq.cpp
        muscle/libMUSCLE/seq.h
        muscle/libMUSCLE/seqvect.cpp
        muscle/libMUSCLE/seqvect.h
        muscle/libMUSCLE/setblosumweights.cpp
        muscle/libMUSCLE/setgscweights.cpp
        muscle/libMUSCLE/setnewhandler.cpp
        muscle/libMUSCLE/spfast.cpp
        muscle/libMUSCLE/sptest.cpp
        muscle/libMUSCLE/stabilize.cpp
        muscle/libMUSCLE/subfam.cpp
        muscle/libMUSCLE/subfams.cpp
        muscle/libMUSCLE/sw.cpp
        muscle/libMUSCLE/termgaps.cpp
        muscle/libMUSCLE/textfile.cpp
        muscle/libMUSCLE/textfile.h
        muscle/libMUSCLE/threadstorage.h
        muscle/libMUSCLE/threewaywt.cpp
        muscle/libMUSCLE/timing.h
        muscle/libMUSCLE/tomhydro.cpp
        muscle/libMUSCLE/traceback.cpp
        muscle/libMUSCLE/tracebackopt.cpp
        muscle/libMUSCLE/tracebacksw.cpp
        muscle/libMUSCLE/tree.h
        muscle/libMUSCLE/treefrommsa.cpp
        muscle/libMUSCLE/types.h
        muscle/libMUSCLE/typetostr.cpp
        muscle/libMUSCLE/unixio.h
        muscle/libMUSCLE/upgma2.cpp
        muscle/libMUSCLE/usage.cpp
        muscle/libMUSCLE/validateids.cpp
        muscle/libMUSCLE/vtml2.cpp
        muscle/libMUSCLE/writescorefile.cpp
        src/csgmum/csg.c
        src/csgmum/csg.h
        src/csgmum/fastaread.c
        src/csgmum/fastaread.h
        src/csgmum/mum.c
        src/csgmum/mum.h
        src/csgmum/types.h
        src/ext/iniFile.cpp
        src/ext/iniFile.h
        src/Converter.cpp
        src/Converter.h
        src/LCB.cpp
        src/LCB.hh
        src/LCR.cpp
        src/LCR.hh
        src/MuscleInterface.cpp
        src/MuscleInterface.h
        src/parsnp.cpp
        src/parsnp.hh
        src/Stack.h
        src/TMum.cpp
        src/TMum.hh)

include_directories(.)
include_directories(muscle)
include_directories(muscle/libMUSCLE)
include_directories(src)
include_directories(src/csgmum)
include_directories(src/ext)

add_executable(parsnp ${SOURCE_FILES})