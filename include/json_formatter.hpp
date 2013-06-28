#ifndef JSON_FORMATTER_HPP
#define JSON_FORMATTER_HPP

#include "output_formatter.hpp"
#include "backend/apidb/cache.hpp"
#include "backend/apidb/changeset.hpp"
#include "json_writer.hpp"
#include <boost/scoped_ptr.hpp>

/**
 * Outputs a JSON-formatted document, which might be useful for javascript
 * or other applications that don't want to parse XML.
 */
class json_formatter 
  : public output_formatter {
private:
  boost::scoped_ptr<json_writer> writer;
  cache<osm_id_t, changeset> &changeset_cache;

  void write_tags(const tags_t &tags);
  void write_common(const element_info &elem);

public:
  // NOTE: takes ownership of the writer!
  json_formatter(json_writer *w, cache<osm_id_t, changeset> &cc);
  virtual ~json_formatter();

  void start_document();
  void end_document();
  void write_bounds(const bbox &bounds);
  void start_element_type(element_type type, size_t num_elements); 
  void end_element_type(element_type type); 
  void error(const std::exception &e);

   void write_node(const element_info &elem, double lon, double lat, const tags_t &tags);
   void write_way(const element_info &elem, const nodes_t &nodes, const tags_t &tags);
   void write_relation(const element_info &elem, const members_t &members, const tags_t &tags);

   void flush();
   void error(const std::string &);
};

#endif /* JSON_FORMATTER_HPP */
