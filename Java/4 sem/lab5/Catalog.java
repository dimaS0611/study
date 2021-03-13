import javax.swing.*;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.TreePath;
import java.awt.*;
import java.util.*;

public class Catalog extends JFrame {

    public static MonumentNode addResult = null;
    public static String path = null;
    JTable infoPanel = new JTable();
    JTree notebooksTree = new JTree();
    ModelTable tableModel = null;
    TreeModel treeModel = null;

    public Catalog() throws HeadlessException {
        JButton addButton = new JButton("Добавить памятник в каталог");
        addButton.addActionListener(e -> SwingUtilities.invokeLater(() -> openAddDialog()));

        JButton removeButton = new JButton("Удалить памятник из каталога");
        removeButton.addActionListener(e -> removeItem());

        tableModel = new ModelTable();
        infoPanel = new JTable(tableModel);
        treeModel = new TreeModel(new treeNode("Каталог"));
        notebooksTree = new JTree(treeModel);
        notebooksTree.addTreeSelectionListener(new TreeSelectionListener() {
            @Override
            public void valueChanged(TreeSelectionEvent e) {
                treeNode node = (treeNode) notebooksTree.getLastSelectedPathComponent();
                if (node == null) {
                    return;
                }
                ArrayList<MonumentNode> array = node.getAllNodes();
                tableModel = new ModelTable(array);
                infoPanel.setModel(tableModel);
            }
        });
        JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, true, new JScrollPane(notebooksTree), new JScrollPane(infoPanel));
        splitPane.setDividerLocation(300);


        getContentPane().add(splitPane);
        getContentPane().add("North", addButton);
        getContentPane().add("South", removeButton);
        setBounds(100, 100, 600, 600);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setVisible(true);
    }


    public void openAddDialog() {
        AddItem addForm = new AddItem(this);
        addForm.setVisible(true);
    }

    public void addNewItem() {
        treeNode temp, where, insert, root = treeModel.getRoot();

        try {
            insert = new treeNode(addResult.number, addResult);
            if ((where = findNode(root, addResult.name)) != null) {
                treeModel.insertNodeInto(insert, where, where.getChildCount(), false);
            } else if (findNode(root, addResult.species) != null) {
                treeModel.insertNodeInto(new treeNode(addResult.name), (temp = findNode(root, addResult.species)), temp.getChildCount(), false);
                where = findNode(root, addResult.name);
                treeModel.insertNodeInto(insert, where, where.getChildCount(), false);
            } else if (findNode(root, addResult.type) != null) {
                treeModel.insertNodeInto(new treeNode(addResult.species), (temp = findNode(root, addResult.type)), temp.getChildCount(), false);
                treeModel.insertNodeInto(new treeNode(addResult.name), (temp = findNode(root, addResult.species)), temp.getChildCount(), false);
                where = findNode(root, addResult.name);
                treeModel.insertNodeInto(insert, where, where.getChildCount(), false);
            } else {
                treeModel.insertNodeInto(new treeNode(addResult.type), root, root.getChildCount(), false);
                treeModel.insertNodeInto(new treeNode(addResult.species), (temp = findNode(root, addResult.type)), temp.getChildCount(), false);
                treeModel.insertNodeInto(new treeNode(addResult.name), (temp = findNode(root, addResult.species)), temp.getChildCount(), false);
                where = findNode(root, addResult.name);
                treeModel.insertNodeInto(insert, where, where.getChildCount(), false);
            }
        } catch (Exception e) {
            path = null;
            addResult = null;
            return;
        }

        path = null;
        addResult = null;
    }

    public void removeItem() {
        TreePath currentSelection = notebooksTree.getSelectionPath();
        if (currentSelection != null) {
            treeNode currentNode = (treeNode) (currentSelection.getLastPathComponent());
            treeNode parent = (treeNode) (currentNode.getParent());
            if (parent != null) {
                treeModel.removeNodeFromParent(currentNode);
                parent.deleteNode(currentNode);
                ArrayList<MonumentNode> array = parent.getAllNodes();
                tableModel = new ModelTable(array);
                infoPanel.setModel(tableModel);
            }
        }
    }

    public treeNode findNode(treeNode root, String s) {
        Enumeration<treeNode> e = root.depthFirstEnumeration();
        while (e.hasMoreElements()) {
            treeNode node = e.nextElement();
            if (node.toString().equalsIgnoreCase(s)) {
                return node;
            }
        }
        return null;
    }
}




