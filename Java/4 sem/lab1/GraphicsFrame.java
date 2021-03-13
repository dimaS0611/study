import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.AffineTransform;
import java.awt.geom.Path2D;
import java.util.Scanner;

public class GraphicsFrame extends JFrame
{
    void setupframe()
    {
        // Here we create the Frame
        JFrame frame = new JFrame(); // create the frame
        frame.setSize(1000,1000);
        frame.setLayout(new BorderLayout());
        frame.setResizable(false);

        frame.setTitle("Task1 - 13");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        frame.setContentPane(new DrawPane());
        frame.setVisible(true);
    }

    static class DrawPane extends JPanel
    {
        private double _angle = 0.0;
        public static int _centre_x = 500;
        public static int _centre_y = 500;
        public static int _radius = 250;

        public DrawPane()
        {
            // setup timer and actions
            new Timer(40, new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    _angle += 4.0;
                    repaint();
                }
            }).start();
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);

            Graphics2D g2d = (Graphics2D) g;

            g.setColor(Color.pink);
            ((Graphics2D) g).setStroke(new BasicStroke(5.0f)); // line thickness
            g.drawOval(_centre_x - _radius, _centre_y - _radius, _radius *2, _radius *2); // draw c circle

            Path2D path = new Path2D.Double();

            path.moveTo(_centre_x, _centre_y - _radius); // triangle drawing starting point
            path.lineTo(_centre_x - (_radius * Math.sqrt(3) / 2), _centre_y + (_radius / 2)); // 2nd point
            path.lineTo(_centre_x + (_radius * Math.sqrt(3) / 2), _centre_y + (_radius / 2)); // 3rd point
            path.closePath();

            AffineTransform transform = new AffineTransform();
            transform.rotate(Math.toRadians(-_angle), _centre_x, _centre_y); // triangle rotating
            Shape transformed = transform.createTransformedShape(path);


            GradientPaint gp = new GradientPaint(_centre_x, _centre_y - _radius,Color.blue,
                    _centre_x, _centre_y + (_radius / 2), Color.pink);  // setup of gradient

            g2d.setPaint(gp);
            g2d.fill(transformed); // drawing a triangle
        }
    }

    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);

        System.out.println("Enter a rotating point(x,y): ");
        DrawPane._centre_x = in.nextInt(); // get X coordinate
        DrawPane._centre_y = in.nextInt(); // get Y coordinate

        System.out.println("Enter a radius of a circle: ");
        DrawPane._radius = in.nextInt(); // get length of radius

        new GraphicsFrame().setupframe();
    }
}

