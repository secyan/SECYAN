//
// Created by Qiwei Li on 6/9/21.
//
#include "Python.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <algorithm>
#include "circuit/share.h"
#include "../core/relation.h"

namespace py = pybind11;

PYBIND11_MODULE(aby, m) {
}

PYBIND11_MODULE(secyan_python, m) {


    py::class_<SECYAN::Relation>(m, "Relation")
            .def(py::init<const SECYAN::Relation::RelationInfo, const SECYAN::Relation::AnnotInfo>())
            .def("loadData", &SECYAN::Relation::LoadData, py::arg("file_path"), py::arg("annot_attr_name"))
            .def("reveal_annot_to_owner", &SECYAN::Relation::RevealAnnotToOwner)
            .def("print", &SECYAN::Relation::Print, py::arg("limit_size"), py::arg("show_zero_annoted_tuple"))
            .def("sort", &SECYAN::Relation::Sort)
            .def("project", py::overload_cast<const char *>(&SECYAN::Relation::Project), py::arg("attr_name"))
            .def("project_names", &SECYAN::Relation::ProjectNames, py::arg("attr_names"))
            .def("aggregate", py::overload_cast<>(&SECYAN::Relation::Aggregate))
            .def("aggregate", py::overload_cast<const char *>(&SECYAN::Relation::Aggregate), py::arg("attr_name"))
            .def("aggregate_names", &SECYAN::Relation::AggregateNames, py::arg("agg_attr_names"))
            .def("annot_add", &SECYAN::Relation::AnnotAdd, py::arg("child"))
            .def("annot_sub", &SECYAN::Relation::AnnotSub, py::arg("child"))
//            .def("annot_div", &SECYAN::Relation::AnnotDiv);
            .def("union", &SECYAN::Relation::Union, py::arg("child"))
            .def("add_attr", &SECYAN::Relation::AddAttr, py::arg("attr_name"), py::arg("attr_type"), py::arg("value"))
            .def("annot_mul", &SECYAN::Relation::AnnotMul, py::arg("indicator"), py::arg("child_annot_permuted"),
                 py::arg("is_child_annot_bool"))
            .def("annot_or_agg", &SECYAN::Relation::AnnotOrAgg)
            .def("semi_join_attr", &SECYAN::Relation::SemiJoinAttr, py::arg("child"), py::arg("parent_attr_name"),
                 py::arg("child_attr_name"))
            .def("semi_join_attrs", &SECYAN::Relation::SemiJoinAttrs, py::arg("child"), py::arg("parent_attr_names"),
                 py::arg("child_attr_names"))
            .def("join_attr", &SECYAN::Relation::JoinAttr, py::arg("child"), py::arg("parent_attr_name"),
                 py::arg("child_attr_name"))
            .def("join_attrs", &SECYAN::Relation::JoinAttrs, py::arg("child"), py::arg("parent_attr_names"),
                 py::arg("child_attr_names"))
            .def("remove_zero_annotated_tuples", &SECYAN::Relation::RemoveZeroAnnotatedTuples)
            .def("reveal_tuples", &SECYAN::Relation::RevealTuples)
            .def("print_table_without_revealing", &SECYAN::Relation::PrintTableWithoutRevealing, py::arg("msg"), py::arg("limit_size"));


    py::enum_<e_role>(m, "E_role")
            .value("SERVER", SERVER)
            .value("CLIENT", CLIENT)
            .value("ALL", ALL);

    py::enum_<SECYAN::Relation::DataType>(m, "DataType")
            .value("INT", SECYAN::Relation::DataType::INT)
            .value("DECIMAL", SECYAN::Relation::DataType::DECIMAL)
            .value("DATE", SECYAN::Relation::DataType::DATE)
            .value("STRING", SECYAN::Relation::DataType::STRING);

    py::class_<SECYAN::Relation::RelationInfo>(m, "RelationInfo")
            .def(py::init<e_role, bool,
                         const std::vector<std::string>,
                         std::vector<SECYAN::Relation::DataType>,
                         size_t, bool>(),
                 py::arg("owner") = SERVER, py::arg("is_public") = true, py::arg("attr_names"),
                 py::arg("attr_types"), py::arg("num_rows") = 100, py::arg("sorted") = true)
            .def_readwrite("owner", &SECYAN::Relation::RelationInfo::owner, "Owner of this relationship")
            .def_readwrite("is_public", &SECYAN::Relation::RelationInfo::isPublic, "Is Public to everyone")
            .def_readwrite("attr_names", &SECYAN::Relation::RelationInfo::attrNames)
            .def_readwrite("attr_types", &SECYAN::Relation::RelationInfo::attrTypes)
            .def_readwrite("num_rows", &SECYAN::Relation::RelationInfo::numRows)
            .def_readwrite("sorted", &SECYAN::Relation::RelationInfo::sorted);


    py::class_<SECYAN::Relation::AnnotInfo>(m, "AnnotInfo")
            .def(py::init<bool, bool>(), py::arg("is_boolean") = true, py::arg("known_by_owner") = true)
            .def_readwrite("is_boolean", &SECYAN::Relation::AnnotInfo::isBoolean)
            .def_readwrite("known_by_owner", &SECYAN::Relation::AnnotInfo::knownByOwner);

}