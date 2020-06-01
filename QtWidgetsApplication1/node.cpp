
#include "node.h"

#include "i_treedata.h"
#include "adapt.h"
#include "tree_data_model.h"

QList<const IAdaptable*> Node::get_child_data() {
    QList<const IAdaptable*> child_data_;
    for (Node* child_node : children) {
        child_data_.append(child_node->data);
    }
    return child_data_;
}

void Node::clear() {
    for (Node* child : children) { child->clear(); }
    qDeleteAll(children);
    children.clear();
}

void Node::refresh(TreeDataModel& model) {
    if (data != nullptr) {
        IAdaptable* data_ = const_cast<IAdaptable*>(data);
        ITreeData* i_tree_data = adapt<ITreeData>(data_);
        if (i_tree_data == nullptr) return;
        QList<IAdaptable*> new_children = i_tree_data->get_children();
        QList<Node*> to_remove;
        QList<const IAdaptable*> to_update;
        QList<const IAdaptable*> to_add;
        // check for removed nodes
        for (Node* child_node : children) {
            IAdaptable* child_data = const_cast<IAdaptable*>(child_node->data);
            if (new_children.indexOf(child_data) == -1) {
                // this node was removed
                to_remove.append(child_node);
            }
        }
        // check for added nodes
        QList<const IAdaptable*> child_data = get_child_data();
        for (const IAdaptable* new_child_data : new_children) {
            if (child_data.indexOf(new_child_data) == -1) {
                to_add.append(new_child_data);
            }
            else {
                to_update.append(new_child_data);
            }
        }

        for (const IAdaptable* new_data : to_add) {
            model.add_child_data(this, new_data);
        }

        for (Node* old_node : to_remove) {
            model.remove_child_node(this, old_node);
        }

        for (const IAdaptable* data : to_update) {
            model.update_data(this, data);
        }
    }
    for (Node* child : children) {
        child->refresh(model);
    }
}
