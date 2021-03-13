import java.awt.*;
import java.awt.event.*;
import java.awt.print.*;
import javax.swing.*;
import java.io.File;
import java.util.*;

public class Printer extends JComponent implements Printable {

    public Printer() {
        JButton button = new JButton("Print");

        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) { printGraph(); }
        });

        this.setLayout(new FlowLayout(FlowLayout.LEFT, 5, 5));
        this.add(button);
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;

        g2d.setColor(Color.WHITE);
        g2d.fillRect(0, 0, this.getWidth(), this.getHeight());

        g2d.setColor(Color.GREEN);
        g2d.setStroke(new MyStroke(2));
        g2d.draw(new CustomShape(40, getX() + getWidth() / 2, getY() + getHeight() / 2));

        g2d.setColor(Color.BLACK);
        g2d.drawString("Линия Локон Аньези", getX() + getWidth() / 2 - 70, getY() + getHeight() - 50);
    }

    public void printGraph() {
        PrinterJob job = PrinterJob.getPrinterJob();
        PageFormat page = job.defaultPage();

        job.setPrintable(this, page);

        if (job.printDialog()) {
            try { job.print(); }
            catch (PrinterException e) { System.err.println(e);  }
        }
    }

    public int print(Graphics g, PageFormat format, int pagenum) {
        if (pagenum > 0)
            return Printable.NO_SUCH_PAGE;

        Graphics2D g2d = (Graphics2D) g;

        g2d.translate(format.getImageableX(), format.getImageableY());

        this.paintComponent(g);
        ArrayList<String> str = new ArrayList<>();
        File f = new File("src/CustomShape.java");

        try {
            Scanner sc = new Scanner(f);
            while(sc.hasNext()){
                str.add(sc.nextLine());
            }
        }
        catch (Exception e){
            System.out.println( e.getMessage() );
        }

        int H = 150;
        int W = 0;
        g2d.setFont(new Font("Arial", Font.PLAIN, 6));
        for (int i = 0; i < str.size()/2; i++) {
            g2d.drawString( str.get(i)  , W,  H );
            H += 8;
        }
        H = 150;
        W = 250;
        for (int i = str.size()/2 + 1; i < str.size(); i++) {
            g2d.drawString( str.get(i)  , W,  H );
            H += 8;
        }

        // Tell the PrinterJob that the page number was valid
        return Printable.PAGE_EXISTS;
    }
}