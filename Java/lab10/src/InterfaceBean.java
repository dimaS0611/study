import javax.swing.*;
import java.awt.*;
import java.beans.*;

public class InterfaceBean extends BeanInfo
{
    private static final int width = 500;
    private static final int height = 300;
    private final JLabel staticText;
    private final JList<String> list;
    private final DefaultListModel<String> model;
    private final JButton submitButton;
    private final JTextArea infoField;

    private final String[] data = new String[100];

    public InterfaceBean()
    {
        JFrame frame = new JFrame();
        JPanel panel = new JPanel();
        frame.setSize(width, height);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        panel.setLayout(new FlowLayout(FlowLayout.CENTER));
        staticText = new JLabel("static text");

        infoField = new JTextArea(5,20);
        infoField.setText("Event info: ");
        infoField.setEnabled(false);

        for(int i = 0; i < 100; i++)
        {
            data[i] = "text" + i;
        }

        model = new DefaultListModel<>();

        list = new JList(model);

        list.setFixedCellHeight(20);
        list.setFixedCellWidth(40);

        list.addListSelectionListener(
                e -> {
                    int elemet = list.getSelectedIndex();
                    generateEventList(elemet);
                });

        submitButton = new JButton("Sumbit");

        submitButton.addActionListener(event -> generateEventButton());

        panel.add(staticText);
        panel.add(submitButton);
        panel.add(infoField);
        panel.add(new JScrollPane(list), BorderLayout.CENTER);

        frame.add(panel);
        frame.setVisible(true);
    }

    int iterator = 0;
    private void generateEventButton() {
        StringBuilder text = new StringBuilder();

        text.append("First button has been selected");
        infoField.setText(text.toString());

        model.addElement(data[iterator]);
        iterator++;
    }

    private void generateEventList(int idx) {
        StringBuilder text = new StringBuilder();
        text.append("List cell has been selected = ").append(idx);
        infoField.setText(text.toString());
    }

    @Override
    public BeanDescriptor getBeanDescriptor() {
        return null;
    }

    @Override
    public EventSetDescriptor[] getEventSetDescriptors() {
        return new EventSetDescriptor[0];
    }

    @Override
    public int getDefaultEventIndex() {
        return 0;
    }

    @Override
    public PropertyDescriptor[] getPropertyDescriptors() {
        return new PropertyDescriptor[0];
    }

    @Override
    public int getDefaultPropertyIndex() {
        return 0;
    }

    @Override
    public MethodDescriptor[] getMethodDescriptors() {
        return new MethodDescriptor[0];
    }

    @Override
    public BeanInfo[] getAdditionalBeanInfo() {
        return new BeanInfo[0];
    }

    @Override
    public Image getIcon(int iconKind) {
        return null;
    }
}
