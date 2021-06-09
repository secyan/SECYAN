//
// Created by Qiwei Li on 6/9/21.
//
#include "Python.h"
#include <pybind11/pybind11.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "circuit/share.h"
#include "circuit/booleancircuits.h"
#include <numeric>
#include <unordered_set>
#include "../core/relation.h"

namespace py = pybind11;

int main(){
    PyObject* pInt;

    Py_Initialize();

    PyRun_SimpleString("import sys\nprint(sys.version)");

    Py_Finalize();
}


PYBIND11_MODULE(aby, m){
py::enum_<e_role>(m, "E_role")
.value("SERVER", SERVER)
.value("CLIENT", CLIENT)
.value("ALL", ALL)
.export_values();
}

PYBIND11_MODULE(SECYAN, m){
py::class_<SECYAN::Relation>(m, "Relation")
.def(py::init<const SECYAN::Relation::RelationInfo, const SECYAN::Relation::AnnotInfo>())
.def("loadData", &SECYAN::Relation::LoadData);
}