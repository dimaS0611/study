import javax.swing.tree.DefaultMutableTreeNode;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;

class treeNode extends DefaultMutableTreeNode {
    String name;
    MonumentNode ifNode = null;
    ArrayList<treeNode> nodes;
    boolean isThisTheEnd = false;

    public treeNode() {
        name = "-";
        nodes = new ArrayList<treeNode>();
        ifNode = null;
        isThisTheEnd = false;
    }

    public treeNode(String str) {
        name = str;
        nodes = new ArrayList<treeNode>();
        ifNode = null;
        isThisTheEnd = false;
    }

    public treeNode(String str, MonumentNode nbNode) {
        name = str;
        nodes = new ArrayList<treeNode>();
        ifNode = nbNode;
        isThisTheEnd = true;
    }

    public ArrayList<MonumentNode> getAllNodes() {
        ArrayList<MonumentNode> ret = new ArrayList<MonumentNode>();
        Deque<treeNode> deque = new ArrayDeque<treeNode>();

        treeNode temp;
        deque.push(this);
        while (!deque.isEmpty()) {
            temp = deque.removeFirst();
            if (temp.isThisTheEnd) {
                ret.add(temp.getIfNode());
            } else {
                for (int i = 0; i < temp.nodes.size(); i++) {
                    deque.push(temp.nodes.get(i));
                }
            }
        }
        return ret;
    }

    public void addNode(treeNode tn) {
        nodes.add(tn);
    }

    public void deleteNode(treeNode tn) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes.get(i).toString().compareToIgnoreCase(tn.toString()) == 0) {
                nodes.remove(i);
            }
        }
    }

    public MonumentNode getIfNode() {
        return ifNode;
    }

    public ArrayList<treeNode> getNodes() {
        return nodes;
    }

    public String toString() {
        return name;
    }
}

