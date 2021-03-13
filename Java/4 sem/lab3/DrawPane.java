import javax.swing.*;
import java.awt.*;
import java.awt.geom.Line2D;

public class DrawPane extends JPanel {
    private int centerX;
    private int centerY;
    private final int paramA = 100;

    private Shape plot;

    @Override
    protected void paintComponent(Graphics g) {     
        g.setColor(Color.WHITE);
        g.fillRect(0, 0, getWidth(), getHeight());
        Graphics2D g2d = (Graphics2D) g;

        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);

        g2d.setStroke(new BasicStroke(3));
        g2d.setColor(Color.WHITE);
        g2d.draw(new Line2D.Double(0, centerY, getWidth(), centerY));
        g2d.draw(new Line2D.Double(centerX, 0, centerX, getHeight()));

        g2d.setColor(Color.GREEN);
        g2d.setStroke(new MyStroke(2f));

        centerX = getWidth() / 2;
        centerY = getHeight() / 2;
        plot = new CustomShape(paramA, centerX, centerY);
        g2d.draw(plot);
    }
}
