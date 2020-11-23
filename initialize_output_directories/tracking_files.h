/*!
  \file tracking_files.h
  \brief class declaration for tracking file handler
  \copyright Released under the MIT License.
  Copyright 2020 Cameron Palmer.
 */
#ifndef INITIALIZE_OUTPUT_DIRECTORIES_TRACKING_FILES_H_
#define INITIALIZE_OUTPUT_DIRECTORIES_TRACKING_FILES_H_

#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "initialize_output_directories/yaml_reader.h"

namespace initialize_output_directories {
class model_matrix {
 public:
  model_matrix() : _id(""), _phenotype("") {}
  model_matrix(const model_matrix &obj)
      : _id(obj._id),
        _phenotype(obj._phenotype),
        _covariates(obj._covariates),
        _ids(obj._ids),
        _data(obj._data) {}
  ~model_matrix() throw() {}

  void set_id(const std::string &id) { _id = id; }

  const std::string &get_id() const { return _id; }

  void set_phenotype(const std::string &phenotype) { _phenotype = phenotype; }

  const std::string &get_phenotype() const { return _phenotype; }

  void set_covariates(const std::vector<std::string> &vec) {
    _covariates = vec;
  }

  void set_covariate(const std::string &s) {
    _covariates.clear();
    _covariates.push_back(s);
  }

  const std::vector<std::string> &get_covariates() const { return _covariates; }

  void load_data(const std::string &filename);

  const std::vector<std::string> get_ids() const { return _ids; }

  const std::vector<std::vector<std::string> > &get_data() const {
    return _data;
  }

  bool operator==(const model_matrix &obj) const {
    if (get_ids().size() != obj.get_ids().size()) return false;
    if (get_data().size() != obj.get_data().size()) return false;
    for (unsigned i = 0; i < get_data().size(); ++i) {
      if (get_data().at(i).size() != obj.get_data().size()) return false;
      for (unsigned j = 0; j < get_data().at(i).size(); ++j) {
        if (get_data().at(i).at(j).compare(obj.get_data().at(i).at(j)))
          return false;
      }
    }
    return true;
  }

 private:
  std::string _id;
  std::string _phenotype;
  std::vector<std::string> _covariates;
  std::vector<std::string> _ids;
  std::vector<std::vector<std::string> > _data;
};

class tracking_files {
 public:
  tracking_files()
      : _output_prefix(""),
        _phenotype_dataset_suffix(""),
        _phenotype_suffix(""),
        _covariates_suffix(""),
        _categories_suffix(""),
        _finalized_suffix("") {}
  tracking_files(const std::string &s, const yaml_reader &config)
      : _output_prefix(s),
        _phenotype_dataset_suffix(""),
        _phenotype_suffix(""),
        _covariates_suffix(""),
        _categories_suffix(""),
        _finalized_suffix("") {
    initialize(config);
  }
  tracking_files(const tracking_files &obj)
      : _output_prefix(obj._output_prefix),
        _phenotype_dataset_suffix(obj._phenotype_dataset_suffix),
        _phenotype_suffix(obj._phenotype_suffix),
        _covariates_suffix(obj._covariates_suffix),
        _categories_suffix(obj._categories_suffix),
        _finalized_suffix(obj._finalized_suffix),
        _general_extensions(obj._general_extensions) {}
  ~tracking_files() throw() {}

  void initialize(const yaml_reader &config);

 private:
  std::string _output_prefix;
  std::string _phenotype_dataset_suffix;
  std::string _phenotype_suffix;
  std::string _covariates_suffix;
  std::string _categories_suffix;
  std::string _finalized_suffix;
  std::map<std::string, std::string> _general_extensions;
};
}  // namespace initialize_output_directories

#endif  // INITIALIZE_OUTPUT_DIRECTORIES_TRACKING_FILES_H_
