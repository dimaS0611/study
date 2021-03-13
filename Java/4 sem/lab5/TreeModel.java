import javax.swing.tree.DefaultTreeModel;

class TreeModel extends DefaultTreeModel {

    private treeNode root;

    public TreeModel(treeNode r) {
        super(r);
        root = r;
    }

    @Override
    public treeNode getRoot() {
        return root;
    }

    public void insertNodeInto(treeNode child, treeNode parent, int i, boolean flag) {
        this.insertNodeInto(child, parent, i);
        parent.addNode(child);
    }
}

