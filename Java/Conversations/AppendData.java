import javafx.stage.Screen;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class AppendData extends JFrame{
    JLabel lName = new JLabel("Имя");
    JLabel lNumber = new JLabel("Номер");
    JLabel lTariff = new JLabel("Тариф");
    JLabel lReduction = new JLabel("Скидка");
    JLabel lDate = new JLabel("Дата");
    JLabel lStart = new JLabel("Начало разговора");
    JLabel lEnd = new JLabel("Конец разговора");

    public static JTextField tfName = new JTextField();
    public static JTextField tfNumber = new JTextField();
    public static JTextField tfTariff = new JTextField();
    public static JTextField tfReduction = new JTextField();
    public static JTextField tfDate = new JTextField();
    public static JTextField tfStart = new JTextField();
    public static JTextField tfEnd = new JTextField();

    JButton bBack = new JButton("Назад");
    JButton bSave = new JButton("Сохранить");

    JPanel panel1 = new JPanel();

    public static int width = 500;
    public static int height = 500;

    AppendData()
    {
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        int locX = (screenSize.width - width) / 2;
        int locY = (screenSize.height - height) / 2;

        setLayout(new GridLayout(8,2,50,20));

        add(lName);
        add(tfName);

        add(lNumber);
        add(tfNumber);

        add(lTariff);
        add(tfTariff);

        add(lReduction);
        add(tfReduction);


        add(lDate);
        add(tfDate);

        add(lStart);
        add(tfStart);

        add(lEnd);
        add(tfEnd);

        add(bBack);

        setBounds(locX, locY, width,height);
        bBack.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });

        add(bSave);
        bSave.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ConversationOut.out(1,0,null);
                tfName.setText("");
                tfNumber.setText("");
                tfTariff.setText("");
                tfReduction.setText("");
                tfDate.setText("");
                tfStart.setText("");
                tfEnd.setText("");
            }
        });
    }

    public static void main(String[] args)
    {
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                try{
                    AppendData frame = new AppendData();
                    frame.setVisible(true);

                }catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
        });
    }

    public static void err()
    {
        String msg = "Недопустимое значение";
        JOptionPane.showMessageDialog(new Frame(), msg, "Dialog", JOptionPane.ERROR_MESSAGE);
    }
}
