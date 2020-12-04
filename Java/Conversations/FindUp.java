import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class FindUp extends JFrame {
    static JTable jTable;

    JButton bFind = new JButton("Найти");
    JButton bBack = new JButton("Назад");
    JButton bName = new JButton("Имя");
    JButton bNumber = new JButton("Номер");

    JTextField textField = new JTextField();

    static JPanel panel = new JPanel();

    String[] headers = {"Имя", "Телефон", "Тариф", "Скидка", "Дата", "Начало разговора", "Конец разговора"};
    static String[][] data = {{"","","","","","",""},{"","","","","","",""},{"","","","","","",""},{"","","","","","",""},{"","","","","","",""}};

    FindUp()
    {
        setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();

        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        setLocationRelativeTo(null);

        setSize(600, 250);
        jTable = new JTable(data, headers){
            @Override
            public boolean isCellEditable(int i, int i1)
            {
                return false;
            }
        };

        jTable.setPreferredScrollableViewportSize(new Dimension(500,100));

        JScrollPane jscrlp = new JScrollPane(jTable);

        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridy = 0;
        c.gridx = 0;
        c.gridheight = 5;
        c.gridwidth = 5;
        c.weightx = 0.4;

        add(jscrlp, c);

        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridy = 5;
        c.gridx = 0;
        c.gridheight = 1;
        c.gridwidth = 5;

        add(textField, c);

        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridy = 6;
        c.gridx = 0;
        // c.gridheight = 1;
        c.gridwidth = 1;

        add(bName, c);

        bName.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                DefaultTableModel dm = new DefaultTableModel();
                dm.fireTableDataChanged();
                String data = textField.getText();
                ConversationOut.out(9,1,data);
            }
        });

        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridy = 6;
        c.gridx = 1;
        // c.gridheight = 1;
        c.gridwidth = 1;

        add(bNumber,c);

        bNumber.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                DefaultTableModel dm = new DefaultTableModel();
                dm.fireTableDataChanged();
                String data = textField.getText();
                ConversationOut.out(9,2,data);
            }
        });



        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridy = 7;
        c.gridx = 0;
        c.gridheight = 1;
        c.gridwidth = 5;

        add(bBack, c);

        bBack.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });

        add(panel);
    }

    public static void fillData(String[][] convData) {

        for (int i = 0; i < convData.length; ++i) {
            for (int j = 0; j < convData[i].length; ++j) {
                jTable.getModel().setValueAt(convData[i][j], i, j);
            }
        }
    }

    public static void showMsgErr()
    {
        JOptionPane.showMessageDialog(JOptionPane.getRootFrame(), "Такой записи не сущуствует!");
    }

    public static void main(String[] args)
    {
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                new FindUp();
            }
        });
    }
}

