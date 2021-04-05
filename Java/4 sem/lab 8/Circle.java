/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab8;


import java.awt.Canvas;
import java.awt.Color;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Shape;
import java.awt.geom.Ellipse2D;
/**
 *
 * @author ASUS
 */
public class Circle extends Canvas{

	private double diameter = 250.0;
	private double x = 100.0, y = 100.0;
	
	public Circle() {}
	
	public Circle(double diameter) {
		this.diameter = diameter;
	}
        
    
    public void paint(Graphics g) {
    	Graphics2D g2 = (Graphics2D) g;
    	Shape ellipse = new Ellipse2D.Double(this.x, this.y, this.diameter, diameter);
    	GradientPaint gp = new GradientPaint((float)this.x, (float)this.y, Color.pink, (float)(this.diameter* 1.5), (float)(this.diameter * 1.5), Color.BLUE);
        
        g2.setPaint(gp);
    	g2.draw(ellipse);
    	g2.fill(ellipse);
    }
	
    
    public void setDiameter(double diameter) {
        this.diameter = diameter;
    }

    public void setX_START_COORDINATE(double x_START_COORDINATE) {
        this.x = x_START_COORDINATE;
    }


    public void setY_COORDINATE(double y_COORDINATE) {
    	this.y = y_COORDINATE;
    }
}