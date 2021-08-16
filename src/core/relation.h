﻿#pragma once
#include <variant>
#include <vector>
#include <string>
#include <unordered_map>
#include "party.h"
#include "aby/abyparty.h"
#include "circuit/booleancircuits.h"
#include <cassert>
//annotation-gen
#include "sqlGen.h"


namespace SECYAN {

    struct DateTime {
        int month;
        int year;
        int day;

        DateTime(int moneth, int year, int day) {
            this->month = moneth;
            this->year = year;
            this->day = day;
        }
    };

    typedef std::variant<
            std::string,
            int,
            DateTime,
            float
    > DynamicListType;


    class Tuple {
    public:
        bool IsDummy() { return isDummy; }

        void ToDummy() { isDummy = true; }

        const uint64_t *data() { return eles.data(); }

        void resize(size_t size) { eles.resize(size); }

        void push_back(uint64_t value) { eles.push_back(value); }

        uint64_t &operator[](int i) {
            assert(!isDummy && "Error: Visiting dummy tuple!");
            return eles[i];
        }

        bool operator<(const Tuple &t) const // dictionary comparison
        {
            if (isDummy) // ensure that a<b and b<a cannot be both true
                return false;
            if (t.isDummy)
                return true;
            auto size = eles.size();
            assert(size == t.eles.size() && size > 0 && "Tuples not comparable!");
            uint32_t i = 0;
            while (i < size && eles[i] == t.eles[i])
                i++;
            return i < size && eles[i] < t.eles[i];
        }

        bool operator==(const Tuple &t) const // dictionary comparison
        {
            if (isDummy || t.isDummy)
                return isDummy && t.isDummy;
            auto size = eles.size();
            assert(size == t.eles.size() && "Tuples not comparable!");
            for (uint32_t i = 0; i < size; i++)
                if (eles[i] != t.eles[i])
                    return false;
            return true;
        }

        Tuple operator+(const Tuple &t) const // concatenate
        {
            assert(!isDummy && !t.isDummy && "Trying to concatenate dummy tuples!");
            Tuple ret;
            ret.eles = this->eles;
            ret.eles.insert(ret.eles.end(), t.eles.begin(), t.eles.end());
            return ret;
        }

    private:
        bool isDummy = false;
        std::vector<uint64_t> eles;
    };

    // Data File Structure:
    // The first line: an integer indicating number of columns in the file
    // The second line: attribute names (and annotation names, e.g. q3_annotation, q8_annotation1)
    // The third line: attribute types (options: int, decimal, date, string, char)
    // The attribute types for annotations can be arbitrary, which do not work
    // Other lines: data

    class Relation {
    public:
        // aggregate function type
        enum AggregateType {
            SUM,
            MAX
        };

        enum DataType {
            INT,
            DECIMAL,
            DATE,
            STRING
        };

        struct RelationInfo {
            std::string displayName = "relation";
            e_role owner;
            bool isPublic; // Indicating whether the other role (not the owner) also knows the tuples of the relation
            std::vector<std::string> attrNames;
            std::vector<DataType> attrTypes;
            size_t numRows;
            bool sorted;
        };

        struct AnnotInfo {
            bool isBoolean;       // Boolean (bitlen=1) or Arithmetic (bitlen=32)
            bool knownByOwner; // Are the annotations known by the owner of the relation
        };

        // Annotation name must NOT be included in attrNames
        Relation(RelationInfo ri, AnnotInfo ai) : m_RI(ri), m_AI(ai) {
            assert(ri.attrNames.size() == ri.attrTypes.size());
            m_Annot.resize(ri.numRows, 0);
        }

        inline bool IsDummy() { return (!m_RI.isPublic) && (m_RI.owner != gParty.GetRole()); }

        // Load data into the relation (for dummy relation, the first two parameters are NULL)
        void LoadData(const char *filePath, std::string anntAttrName);

        void RevealAnnotToOwner();

        // reveal annotations to the owner
        void Print(size_t limit_size = 100, bool showZeroAnnotedTuple = false); // only be called after revealed
        /**
         * Return the print results into a 2d vector.
         * If the result is empty vector, then it is a dummy results.
         * Otherwise, the first row will be the header, the rest will be the real data
         *
         * @param limt_size maximun number of rows
         * @param showZeroAnnotedTuple
         * @return
         */
        std::vector<std::vector<DynamicListType>>
        ReturnPrintResults(size_t limt_size = 100, bool showZeroAnnotedTuple = false);

        void Sort();

        // Note: this project operation does not elimiate duplicate tuples!
        void Project(std::vector<std::string> &projectAttrNames);

        void Project(const char *projectAttrName);

        void ProjectNames(std::vector<std::string> &projectAttrNames);

//        void Aggregate();
//
//        void Aggregate(const char *aggAttrName);
//
//        void Aggregate(std::vector<std::string> &aggAttrNames);

        // Aggregate func
        void Aggregate(AggregateType aggType);
        void Aggregate(AggregateType aggType, const char *aggAttrName);
        void Aggregate(AggregateType aggType, std::vector<std::string> &aggAttrNames);
        // if no Type parameters are passed into Aggregate() , default call AggregateSum();
        // the following three funcs can be eliminated if we want Aggregate(param) must have a param which has type of AggregateType
        // if eliminated, Aggregate funcs in TPCH.cpp should be updated under the restriction above.
        void Aggregate();
        void Aggregate(const char *aggAttrName);
        void Aggregate(std::vector<std::string> &aggAttrNames);
        // specified aggregate_function
        void AggregateSum();
        void AggregateMax();
        // for python wrapper
        void AggregateNames(AggregateType aggType, std::vector<std::string> &aggAttrNames);
        void AggregateNames_tbd(std::vector<std::string> &aggAttrNames);

        void AnnotAdd(Relation &child);

        void AnnotSub(Relation &child);

        void AnnotDiv(Relation &child); // not implemented yet!
        void Union(Relation &child);

        void AddAttr(const char *attrName, DataType attrType, uint64_t value);

        void AnnotMul(uint32_t *indicator, uint32_t *childAnnotPermuted, bool isChildAnnotBool);

        // This corresponds to the pi_1 operator, which eliminates duplicate tuples (to zero-annotated dummy tuples)
        // It sets annotation of a tuple as 1 if at least one of its duplicates has non-zero annotation
        void AnnotOrAgg();

        void
        SemiJoin(Relation &child, std::vector<std::string> &parentAttrNames, std::vector<std::string> &childAttrNames);
        // Note: the order of attrNames corresponds to join attributes of the two relations

        void SemiJoin(Relation &child, const char *parentAttrName, const char *childAttrName);

        void SemiJoinAttr(Relation &child, const char *parentAttrName, const char *childAttrName);

        void SemiJoinAttrs(Relation &child, std::vector<std::string> &parentAttrNames,
                           std::vector<std::string> &childAttrNames);

        void RemoveZeroAnnotatedTuples();

        void RevealTuples();

        void Join(Relation &child, std::vector<std::string> &parentAttrNames, std::vector<std::string> &childAttrNames);

        void Join(Relation &child, const char *parentAttrName, const char *childAttrName);

        void
        JoinAttrs(Relation &child, std::vector<std::string> &parentAttrNames, std::vector<std::string> &childAttrNames);

        void JoinAttr(Relation &child, const char *parentAttrName, const char *childAttrName);

        // For debug test only
        void PrintTableWithoutRevealing(const char *msg = NULL, int limit_size = 100);

        // return annot_gen sql
        std::string annotSqlGen(std::string query, std::string annot_name, std::string relation_name);

    private:
        RelationInfo m_RI;
        AnnotInfo m_AI;
        std::vector<Tuple> m_Tuples;
        std::vector<uint32_t> m_Annot; // the annotations of this relation

        uint64_t HashTuple(int i);

        void PermuteAnnotByOwner(std::vector<uint32_t> &permutedIndices);

        void AliceSemiJoin(Relation &BobRelation);

        void BobSemiJoin(Relation &BobRelation);

        void OblivSemiJoin(Relation &child, std::vector<std::string> &parentAttrNames,
                           std::vector<std::string> &childAttrNames);

        void OblivAnnotOrAgg();

        void OwnerAnnotAddAgg();

        void OblivAnnotMaxAgg();

        void OwnerAnnotMaxAgg();

        std::vector<uint64_t> PackTuples();
    };

} // namespace SECYAN



