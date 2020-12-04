using System;
using System.Collections.Generic;
using System.IO;

namespace BinaryTree
{
    public class TreeNode
    {
        public TreeNode left { get; set; }
        public TreeNode right { get; set; }

        public TreeNode parent { get; set; }

        int m_data = 0;
        public int data { get { return m_data; } set { m_data = data; } }

        public int m_halfPath { get; set; }
        public int sum { get; set; }
        public int height { get; set; } 
        public TreeNode(int data, TreeNode parent)
        {
            m_data = data;
            left = null;
            right = null;
            this.parent = parent;
        }

        public void replaceChild(TreeNode child, TreeNode another)
        {
            if (left == child)
                left = another;
            else if (right == child)
                right = another;
        }
    }

    public class MaxDistanceFinder
    {
        TreeNode m_bestNode = null;
        int m_maxDistance = 0;
        int m_minSum = 0;

        public TreeNode bestNode { get { return m_bestNode; } }
        public int maxDistance { get { return m_maxDistance; } }
        public int minSum { get { return m_minSum; } }
        
        // возвращает максимальное растояние
        int processNode(TreeNode node, out int minSum)
        {
            minSum = node.data;

            if (node.left == null && node.right == null)
                return 1;

            int d2 = 0, s2 = 0;
            if (node.right != null)
                d2 = processNode(node.right, out s2);

            int d1=0, s1 = 0;
            if (node.left != null)
                d1 = processNode(node.left, out s1);

            int sum = s1 + s2;
            int dist = d1 + d2;
           
            if(dist > m_maxDistance || dist == m_maxDistance && sum < m_minSum)
            {
                m_bestNode = node;
                m_maxDistance = dist;
                m_minSum = sum;
            }

            if(d1 >= d2)
            {
                minSum = s1;
                return d1 + 1;
            }

            minSum = s2;
            return d2 + 1;
        }

        public TreeNode find(TreeNode node)
        {
            int minSum = 0;
            processNode(node, out minSum);
            return m_bestNode;
        }
    }


    public class BinaryTree
    {
        

        public TreeNode root = null;
        private StreamWriter sw = new StreamWriter("out.txt");
        public BinaryTree()
        { }
        public BinaryTree(int value)
        {
            root = new TreeNode(value, null);
        }

        public void finalize()
        {
            sw.Close();
        }



        public void Add(int data)
        {
            if (root == null)
            {
                root = new TreeNode(data, null);
                return;
            }

            TreeNode currentNode = root;

            while (currentNode != null)
            {
                if (data >= currentNode.data)
                {
                    if (currentNode.right == null)
                    {
                        currentNode.right = new TreeNode(data, currentNode);
                        return;
                    }
                    currentNode = currentNode.right;
                    continue;
                }


                if (currentNode.left == null)
                {
                    currentNode.left = new TreeNode(data, currentNode);
                    return;
                }
                currentNode = currentNode.left;
            }
        }

        public void leftOrder(BinaryTree tree)
        {
            tree.preOrder(root);
        }

        private void preOrder(TreeNode node)
        {
            if (node == null) { return; }

            sw.WriteLine(node.data);
            Console.WriteLine(node.data);

            preOrder(node.left);
            preOrder(node.right);
        }
        
        // удалить из дерева корень root узел со значением data
        public void DeleteNode(int data)
        {
            TreeNode node = FindNode(root, data);
            if (node == null)
                return;

            TreeNode left = node.left;
            TreeNode right = node.right;
            TreeNode parent = node.parent;

            if (right == null)
            {
                if (parent != null)
                    parent.replaceChild(node, left);
                else
                    root = left;
                return;
            }

            if (parent != null)
                parent.replaceChild(node, right);
            else
                root = right;

            if (left == null)
                return;

            TreeNode leastRightLeft = findMinNode(right);

            leastRightLeft.left = left;
        }

        static TreeNode findMinNode(TreeNode node)
        {
            while (node.left != null)
                node = node.left;
            return node;
        }

        static TreeNode FindNode(TreeNode node, int data)
        {
            if (node == null)
                return null;

            if (data > node.data)
                return FindNode(node.right, data);
            if (data < node.data)
                return FindNode(node.left, data);
            if (data == node.data)
                return node;
            else
                return null;
        }

        public TreeNode Find(int data)
        {
            return FindNode(root, data);
        }

        public void CompMaxPath(TreeNode root, ref int max)
        {
            if (root != null)
            {
                max = Math.Max(max, root.m_halfPath);
                CompMaxPath(root.left, ref max);
                CompMaxPath(root.right, ref max);
            }
        }

        public void FindNode(TreeNode root, int max, ref List<TreeNode> listNode)
        {
            if (root != null)
            {
                if (root.m_halfPath == max)
                {
                    listNode.Add(root);
                }

                FindNode(root.left, max, ref listNode);
                FindNode(root.right, max, ref listNode);
            }
        }

        private int _Diameter(TreeNode root)
        {
            if (root == null)
                return 0;

            int lHeight = _Height(root.left);
            int rHeight = _Height(root.right);

            int lDiametr = _Diameter(root.left);
            int rDiametr = _Diameter(root.right);

            return Math.Max(lHeight + rHeight + 1, Math.Max(lDiametr, rDiametr));
        }

        public int Diameter()
        {
            return _Diameter(root);
        }

        private int _Height(TreeNode root)
        {
            if (root == null)
                return 0;

            return root.height = (1 + Math.Max(_Height(root.left), _Height(root.right)));
        }

        public int Height()
        {
            return _Height(root);
        }

        public void halfPath(TreeNode root)
        {
            if (root != null)
            {
                root.m_halfPath = 0;
                int lPath = _Height(root.left);
                int rPath = _Height(root.right);

                if (root.left != null)
                {
                    root.m_halfPath += lPath;
                    root.m_halfPath += 1;
                }

                if (root.right != null)
                {
                    root.m_halfPath += rPath;
                    root.m_halfPath += 1;
                }

                halfPath(root.left);
                halfPath(root.right);
            }
        }

        public int FindDataOfSum(TreeNode tn)
        {
            int data;
                TreeNode node = tn.left;
                while (node.height != 0)
                {
                    if (node.left != null)
                    {
                        if (node.left.height == (node.height - 1))
                            node = node.left;
                        else
                            node = node.right;
                    }
                    else if (node.right != null)
                        node = node.right;
                    else
                        break;
                }

                data = node.data;


            return data;

        }

        public void FindMinSum(List<TreeNode> listNode)
        {
            foreach (TreeNode tn in listNode)
            {
                if (tn.left != null)
                {
                    TreeNode node = tn.left;
                    while (node.height != 0)
                    {
                        if (node.left != null)
                        {
                            if (node.left.height == (node.height - 1))
                                node = node.left;
                            else
                                node = node.right;
                        }
                        else if (node.right != null)
                            node = node.right;
                        else
                            break;
                    }
                    
                    tn.sum = node.data;
                }
                else 
                    tn.sum = tn.data;
                
                if (tn.right != null)
                {
                    TreeNode node = tn.right;
                    while (node.height != 0)
                    {
                        if (node.left != null)
                        {
                            if (node.left.height == (node.height - 1))
                            {
                                node = node.left;
                            }
                            else 
                                node = node.right;
                        }
                        else if (node.right != null)
                            node = node.right;
                        else
                            break;
                    }
                    tn.sum += node.data;
                }
                else
                {
                    if (tn.left != null)
                        tn.sum += tn.data;
                }
            }
        }

        public void solver()
        {
            _Height(root);
            halfPath(root);

            int maxPath = 0;
            maxPath = root.m_halfPath;

            CompMaxPath(root, ref maxPath);

            List<TreeNode> listNode = new List<TreeNode>();
            FindNode(root, maxPath, ref listNode);

            FindMinSum(listNode);

            int minSum = 0;
            minSum = listNode[0].sum;

            foreach (TreeNode tr in listNode)
                minSum = Math.Min(minSum, tr.sum);

            int idxNode = 0;
            int size = listNode.Count;
            for(idxNode = 0; size >= idxNode && listNode[idxNode].sum != minSum; ++idxNode) { }

            int rootTree;
            rootTree = listNode[idxNode].data;

            DeleteNode(rootTree);
        }

    }


    class Program
    {
        /*
        static void verifyNode(TreeNode node)
        {
            if (node == null)
                return;
            if (node.left != null && node.right != null)      
                Debug.Assert(node.left.data >= node.right.data);
            verifyNode(node.left);
            verifyNode(node.right);              
        }
        */

        static void Main(string[] args)
        {
            BinaryTree tree = new BinaryTree();
            
            using (var sr = new StreamReader("in.txt"))
            {
                string ch;
                while (!sr.EndOfStream)
                {
                    ch = sr.ReadLine();
                    tree.Add(int.Parse(ch));
                }
            }

            tree.solver();

            tree.leftOrder(tree);

            tree.finalize();
        }
    }
}
