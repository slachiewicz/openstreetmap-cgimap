#ifndef DATA_SELECTION_HPP
#define DATA_SELECTION_HPP

#include "types.hpp"
#include "output_formatter.hpp"

#include <list>

/** 
 * represents a selected set of data which can be written out to
 * an output_formatter and manipulated by a nice set of commands
 * suited for OSM relational data manipulations.
 */
class data_selection {
public:
	 enum visibility_t {
		 exists,
		 deleted,
		 non_exist
	 };

	 virtual ~data_selection();

	 /******************* output functions ************************/

	 /// write the nodes to an output formatter
	 virtual void write_nodes(output_formatter &formatter) = 0;
	 
	 /// write the ways to an output formatter
	 virtual void write_ways(output_formatter &formatter) = 0;

	 /// write the relations to an output formatter
	 virtual void write_relations(output_formatter &formatter) = 0;

	 /******************* information functions *******************/

	 /// the number of currently selected nodes
	 virtual int num_nodes() = 0;

	 /// the number of currently selected ways
	 virtual int num_ways() = 0;

	 /// the number of currently selected relations
	 virtual int num_relations() = 0;

	 // check if the node is visible, deleted or has never existed
	 virtual visibility_t check_node_visibility(id_t id) = 0;

	 // check if the way is visible, deleted or has never existed
	 virtual visibility_t check_way_visibility(id_t id) = 0;

	 // check if the relation is visible, deleted or has never existed
	 virtual visibility_t check_relation_visibility(id_t id) = 0;

	 /******************* manipulation functions ******************/

	 /// select the nodes in the list, where they are visible
	 virtual void select_visible_nodes(const std::list<id_t> &) = 0;

	 /// select the ways in the list, where they are visible
	 virtual void select_visible_ways(const std::list<id_t> &) = 0;

	 /// select the relations in the list, where they are visible
	 virtual void select_visible_relations(const std::list<id_t> &) = 0;

   /// given a bounding box, select nodes within that bbox up to a limit of max_nodes
	 virtual void select_nodes_from_bbox(const bbox &bounds, int max_nodes) = 0;

   /// selects the node members of any already selected relations
	 virtual void select_nodes_from_relations() = 0;
	 
   /// selects all ways that contain selected nodes
	 virtual void select_ways_from_nodes() = 0;
	 
   /// selects all ways that are members of selected relations
	 virtual void select_ways_from_relations() = 0;
	 
   /// select all relations that contain selected ways
	 virtual void select_relations_from_ways() = 0;
	 
   /// select nodes which are used in selected ways
	 virtual void select_nodes_from_way_nodes() = 0;
	 
   /// select relations which include selected nodes 
	 virtual void select_relations_from_nodes() = 0;
	 
   /// update relations to include relations which have node members
	 /// which are used in already selected ways.
	 virtual void select_relations_from_way_nodes() = 0;
	 
   /// select relations which include selected relations
	 virtual void select_relations_from_relations() = 0;
	 
};

#endif /* DATA_SELECTION_HPP */