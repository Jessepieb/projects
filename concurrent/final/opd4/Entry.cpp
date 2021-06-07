#include "Entry.h"

void to_json(json& j, const Entry& e) {
	j = json{  "Entry",
	{ {"loc_name", e.loc_name},
	{"src_dir", e.src_directory},
	{"dst_dir", e.dst_directory},
	{"keywords", e.keywords},
	{"extensions", e.extensions},
	{"sort_files", e.sort_files},
	{"sort_dir", e.sort_dir} }
};
}

Entry from_json(json& new_j) {
	Entry e;
	new_j.at("loc_name").get_to(e.loc_name);
	new_j.at("src_dir").get_to(e.src_directory);
	new_j.at("dst_dir").get_to(e.dst_directory);
	new_j.at("keywords").get_to(e.keywords);
	new_j.at("extensions").get_to(e.extensions);
	new_j.at("sort_files").get_to(e.sort_files);
	new_j.at("sort_dir").get_to(e.sort_dir);

	return e;
};
