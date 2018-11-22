/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package imgutil;

import constants.Constant;
import gui.GUI;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

/**
 *
 * @author alex
 */
public class SubImage implements Constant{

    public static void getSubImages(GUI frame, String folder, Rectangle rect) {
        String[] list;
        list = Find.getImagesInFolder(folder);
        for (int i = 0; i < list.length; i++) {
            try {
                String name = list[i];
                String img_path = folder + name;
                BufferedImage originalImage = ImageIO.read(new File(img_path));
                int width = originalImage.getWidth();
                int height = originalImage.getHeight();
                frame.setTextArea("[" + i + "] reading image" + " width:" + width + " height:" + height + " name:" + list[i]);
                String[] names = name.split("\\.");
                String new_path = folder + names[0];
                File dir = new File(new_path);
                if (!dir.isDirectory()) {
                    if (dir.mkdir()) {
                        System.out.println("creating directory " + new_path);
                        frame.setTextArea("creating directory " + new_path);
                    } else {
                        System.out.println("can't create directory, return");
                        frame.setTextArea("can't create directory, return");
                        return;
                    }
                }
                int counter = 0;
                for (int x = 0; x < width - rect.width; x += rect.width) {
                    for (int y = 0; y < height - rect.height; y += rect.height) {
                        BufferedImage crop_image = originalImage.getSubimage(x, y, rect.width, rect.height);
                        String new_name = names[0] + String.valueOf(counter) + ".jpg";
                        //frame.setTextArea("  writing image width:" + width_new + " height:" + height_new + " name:" + new_name);
                        ImageIO.write(crop_image, "jpg", new File(new_path + DIV_DIRECTORY + new_name));
                        counter++;
                    }
                }
            } catch (IOException e) {
                System.out.println(e.getMessage());
                frame.setTextArea(e.getMessage());
            }
        }
    }

    public static void main(String[] args) {
        GUI gui = new GUI();
        Rectangle rect = new Rectangle(0, 0, 100, 100);
        String path = "C:\\Temp\\test\\cat\\";
        getSubImages(gui, path, rect);
    }
}
