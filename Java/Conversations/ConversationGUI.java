
import com.sun.java.swing.plaf.motif.MotifLookAndFeel;
import com.sun.java.swing.plaf.windows.WindowsLookAndFeel;

import javax.swing.*;
import javax.swing.plaf.metal.MetalLookAndFeel;
import javax.swing.plaf.nimbus.NimbusLookAndFeel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;

public class ConversationGUI {
    JPanel rootPanel;


    JMenu file = new JMenu("File");
    JMenu view = new JMenu("View");
    JMenu help = new JMenu("Help");
    JMenu theme = new JMenu("Theme");

    JMenuItem quit = new JMenuItem("Quit");
    JMenuItem about = new JMenuItem("About");
    JMenuItem jiMetal = new JMenuItem("Metal");
    JMenuItem jiWindows = new JMenuItem("Windows");
    JMenuItem jiMotif = new JMenuItem("Motif");
    JMenuItem jiNimbus = new JMenuItem("Nimbus");
    JMenuBar jMenuBar = new JMenuBar();

    JFrame mainFrame = new JFrame("Telephone conversations");


    public static int width = 300;
    public static int height = 570;


    ConversationGUI() {

        AppendData ap = new AppendData();

        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        int locX = (screenSize.width - width) / 2;
        int locY = (screenSize.height - height) / 2;

        mainFrame.setVisible(true);

        JPanel pMenu = new JPanel();

        pMenu = menu();

        mainFrame.add(pMenu);

        file.add(quit);
        view.add(theme);
        help.add(about);

        theme.add(jiMetal);
        theme.add(jiMotif);
        theme.add(jiWindows);
        theme.add(jiNimbus);

        quit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(1);
                mainFrame.dispose();
            }
        });
        about.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JOptionPane.showMessageDialog(JOptionPane.getRootFrame(), "Developed by Dmitry Semenovich 2nd year 13 grope FAMCS BSU");
            }
        });

        jiMetal.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    UIManager.setLookAndFeel(new MetalLookAndFeel());
                    SwingUtilities.updateComponentTreeUI(mainFrame);
                    mainFrame.pack();
                } catch (UnsupportedLookAndFeelException unsupportedLookAndFeelException) {
                    unsupportedLookAndFeelException.printStackTrace();
                }
            }
        });

        jiMotif.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    UIManager.setLookAndFeel(new MotifLookAndFeel());
                    SwingUtilities.updateComponentTreeUI(mainFrame);
                    mainFrame.pack();
                } catch (UnsupportedLookAndFeelException unsupportedLookAndFeelException) {
                    unsupportedLookAndFeelException.printStackTrace();
                }
            }
        });

        jiWindows.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    UIManager.setLookAndFeel(new WindowsLookAndFeel());
                    SwingUtilities.updateComponentTreeUI(mainFrame);
                    mainFrame.pack();
                } catch (UnsupportedLookAndFeelException unsupportedLookAndFeelException) {
                    unsupportedLookAndFeelException.printStackTrace();
                }
            }
        });

        jiNimbus.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    UIManager.setLookAndFeel(new NimbusLookAndFeel());
                    SwingUtilities.updateComponentTreeUI(mainFrame);
                    mainFrame.pack();
                } catch (UnsupportedLookAndFeelException unsupportedLookAndFeelException) {
                    unsupportedLookAndFeelException.printStackTrace();
                }
            }
        });
        jMenuBar.add(file);
        jMenuBar.add(view);
        jMenuBar.add(help);


        mainFrame.setJMenuBar(jMenuBar);

        mainFrame.setBounds(locX, locY, width, height);

        mainFrame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                int confirm = JOptionPane.showConfirmDialog(mainFrame, "Закрыть ?", "Выход", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null);

                if(confirm == JOptionPane.YES_OPTION)
                {
                    System.exit(1);
                    mainFrame.dispose();
                }
                else
                {
                    mainFrame.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
                }
            }
        });

    }

    public static JPanel menu()
    {
        JPanel panel = new JPanel();

        JButton bAddInfo = new JButton("Добавить запись");
        JButton bDelete = new JButton("Очистить файл");
        JButton bPrint = new JButton("Все записи");
        JButton bSortBy = new JButton("Сортировать по значению");
        JButton bDeleteBy = new JButton("Удалить по значению");
        JButton bFind = new JButton("Поиск");
        JButton bFindUp = new JButton("Поиск\n на позицию ниже");
        JButton bFindDown = new JButton("Поиск\n на позицию выше");

        panel.setLayout(new GridLayout(8,1, 10, 10));

        panel.add(bAddInfo);

        bAddInfo.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                AppendData appendData = new AppendData();
                appendData.setVisible(true);
            }
        });

        panel.add(bDelete);

        bDelete.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ConversationOut.out(3,0,null);
                JOptionPane.showMessageDialog(panel,"Все записи удалены!" );
            }
        });

        panel.add(bPrint);


        bPrint.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ConversationOut.out(5,0,null);
                Print print = new Print();
                print.setVisible(true);
            }
        });

        panel.add(bSortBy);

        bSortBy.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                PrintSorted printSorted = null;
                try {
                    printSorted = new PrintSorted();
                } catch (IOException | ClassNotFoundException ioException) {
                    ioException.printStackTrace();
                }
                printSorted.setVisible(true);
            }
        });

        panel.add(bDeleteBy);

        bDeleteBy.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                DeleteBy deleteBy = new DeleteBy();
                deleteBy.setVisible(true);
            }
        });

        panel.add(bFind);

        bFind.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Find find = new Find();
                find.setVisible(true);
            }
        });

        panel.add(bFindUp);

        bFindUp.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                FindUp findUp = new FindUp();
                findUp.setVisible(true);
            }
        });

        panel.add(bFindDown);

        bFindDown.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                FindDown findDown = new FindDown();
                findDown.setVisible(true);
            }
        });

        panel.setVisible(true);

        return panel;
    }

}
