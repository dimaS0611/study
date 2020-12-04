import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class DeleteBy extends JFrame{
    JButton bBack = new JButton("Назад");
    JButton bName = new JButton("Имя");
    JButton bNumber = new JButton("Номер");

    JTextField textField = new JTextField();

    public static JPanel panel = new JPanel();

    DeleteBy() {

        setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();

        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        setSize(450, 80);

        setLocationRelativeTo(null);
        setVisible(true);

        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 0;
        c.gridy = 0;
        c.weightx = 0.5;
        c.gridheight = 1;
        c.gridwidth = 2;

        panel.add(textField, c);

        textField.setText("Значение для удаления");

        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 0;
        c.gridy = 1;
        c.weightx = 0.5;
        c.gridheight = 1;
        c.gridwidth = 1;

        panel.add(bName,c);

        bName.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String data = textField.getText();
                ConversationOut.out(4,1,data);
            }
        });

        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 1;
        c.gridy = 1;
        c.weightx = 0.5;
        c.gridheight = 1;
        c.gridwidth = 1;

        panel.add(bNumber,c);

        bNumber.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String data = textField.getText();
                ConversationOut.out(4,2,data);
            }
        });

        c.fill = GridBagConstraints.HORIZONTAL;
        c.gridx = 0;
        c.gridy = 2;
        c.weightx = 0.5;
        c.gridheight = 1;
        c.gridwidth = 2;

        panel.add(bBack);

        bBack.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });

        add(panel);

        setResizable(false);
    }

    public static void showMsgErr()
    {
        JOptionPane.showMessageDialog(panel, "Такой записи не сущуствует!");
    }

    public static void showMsg()
    {
        JOptionPane.showMessageDialog(panel,"Запись удалена!" );
    }


    public static void main(String[] args)
    {
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                new DeleteBy();
            }
        });
    }
}
