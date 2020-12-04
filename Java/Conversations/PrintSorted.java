import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class PrintSorted extends JFrame {
    JButton bName = new JButton("Имя");
    JButton bNumber = new JButton("Номер");
    JButton bBack = new JButton("Назад");

    public static JTable jTable;

    public static String[][] data ;
    public static String[] headers = {"Имя", "Телефон", "Тариф", "Скидка", "Дата", "Начало разговора", "Конец разговора"};

    PrintSorted() throws IOException, ClassNotFoundException {
        data = ConversationOut.printFile();
        setLayout(new GridBagLayout());

        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        GridBagConstraints c = new GridBagConstraints();

        setSize(1000, 520);

        jTable = new JTable(data, headers){
            @Override
            public boolean isCellEditable(int i, int i1)
            {
                return false;
            }
        };

        JScrollPane jscrlp = new JScrollPane(jTable);

        c.fill =  GridBagConstraints.BOTH;
        c.weightx = 0.5;
        c.gridx = 0;
        c.gridy = 0;
        c.gridwidth = 4;
        c.gridheight = 2;

        add(jscrlp,c);

        setLocationRelativeTo(null);
        setVisible(true);

        c.weightx = 0.5;
        c.gridy = 2;
        c.gridx = 0;
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridwidth = 1;

        add(bName, c);

        bName.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                DefaultTableModel dm = new DefaultTableModel();
                dm.fireTableDataChanged();
                ConversationOut.out(6,1,null);
            }
        });

        c.weightx = 0.5;
        c.gridy = 2;
        c.gridx = 1;
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridwidth = 1;

        add(bNumber, c);

        bNumber.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                DefaultTableModel dm = new DefaultTableModel();
                dm.fireTableDataChanged();
                ConversationOut.out(6,2,null);
            }
        });

        c.weightx = 0.5;
        c.gridy = 4;
        c.gridx = 0;
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridwidth = 4;

        add(bBack, c);

        bBack.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });

        setResizable(false);
    }

    public static void fillData(String[][] convData) {
        data = convData;
    }

    public static void refillData(String[][] convData) {
        for(int i =0; i < convData.length; ++i)
        {
            for(int j = 0; j < convData[i].length; ++j)
            {
                jTable.getModel().setValueAt(convData[i][j], i, j);
            }
        }
    }


    public static void main(String[] args)
    {
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                try {
                    new PrintSorted();
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (ClassNotFoundException e) {
                    e.printStackTrace();
                }
            }
        });
    }

}
