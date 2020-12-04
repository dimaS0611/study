import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Print extends JFrame {

    String[] headers = {"Имя", "Телефон", "Тариф", "Скидка", "Дата", "Начало разговора", "Конец разговора"};
    static String[][] data;

    JTable jTabPhones;
    JButton bBack = new JButton("Назад");
    Print() {

        setLayout(new GridBagLayout());

        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        GridBagConstraints c = new GridBagConstraints();

        setSize(1000, 500);
        jTabPhones = new JTable(data, headers){
            @Override
            public boolean isCellEditable(int i, int i1)
            {
                return false;
            }
        };


        JScrollPane jscrlp = new JScrollPane(jTabPhones);

        c.fill =  GridBagConstraints.HORIZONTAL;
        c.weightx = 0.5;
        c.gridx = 0;
        c.gridy = 0;
        c.gridwidth = 2;

        add(jscrlp,c);

        setLocationRelativeTo(null);
        setVisible(true);

        c.weightx = 0.5;
        c.gridy = 1;
        c.gridx = 0;
        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridwidth = 1;

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


    public static void main(String[] args)
    {
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                new Print();
            }
        });
    }
}
