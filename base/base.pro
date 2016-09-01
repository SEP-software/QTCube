INCLUDEPATH += . .. ../base ../gui ${SEP}/include
WARNINGS += -Wnone
 
TEMPLATE = lib
MOC_DIR = mocs
CONFIG+=staticlib
OBJECTS_DIR = objs

HEADERS+=\ 
hypercube.h\ 
axis.h\ 
float_1d.h\ 
float_2d.h\ 
hypercube_float.h\ 
percentile.h\ 
norm_vector.h\ 
l2_norm.h\ 
norm.h\ 
my_vector.h\ 
sreg.h\ 
param_func.h\ 
lloyd_1d.h\ 
lloyd.h\ 
fastmarch.h\ 
pqueue.h\ 
sregf.h\ 
viterbi.h\ 
my_score.h\ 
dynamic.h\ 
sep_params.h\ 
path.h
SOURCES+=\ 
hypercube.cpp\ 
axis.cpp\ 
float_1d.cpp\ 
float_2d.cpp\ 
hypercube_float.cpp\ 
percentile.cpp\ 
norm_vector.cpp\ 
l2_norm.cpp\ 
sreg.cpp\ 
param_func.cpp\ 
lloyd_1d.cpp\ 
lloyd.cpp\ 
fastmarch.cpp\ 
pqueue.cpp\ 
sregf.cpp\ 
viterbi.cpp\ 
dynamic.cpp\ 
sep_params.cpp\ 
path.cpp
