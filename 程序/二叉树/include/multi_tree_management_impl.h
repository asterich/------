#ifndef __MULTI_TREE_MANAGEMENT_IMPL_H_
#define __MULTI_TREE_MANAGEMENT_IMPL_H_

#include "binary_tree_impl.h"
#include "multi_tree_management.h"

status append(MultiTreeTable &trees, const char *tree_name);
status remove(MultiTreeTable &trees, const char *tree_name);
status locate(MultiTreeTable &trees, const char *tree_name);

#endif