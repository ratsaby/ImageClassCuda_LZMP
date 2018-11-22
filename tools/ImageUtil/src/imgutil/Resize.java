/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package imgutil;

import constants.Constant;
import gui.GUI;
import java.awt.AlphaComposite;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.Vector;
import javax.imageio.ImageIO;
import javax.swing.JFrame;

/**
 *
 * @author alex
 */
public class Resize implements Constant{

    private static final int IMG_WIDTH = 100;
    private static final int IMG_HEIGHT = 100;



    public static void resizeImagesFromFolder(String folder, String name, int max_size) {
        String[] list;
        String new_path = folder + name;
        File dir = new File(new_path);

        if (!dir.isDirectory()) {
            if (dir.mkdir()) {
                System.out.println("creating directory " + new_path);
            } else {
                System.out.println("can't create directory, return");
                return;
            }
        }
        list = Find.getImagesInFolder(folder);
        for (int i = 0; i < list.length; i++) {
            try {
                BufferedImage originalImage = ImageIO.read(new File(folder + list[i]));
                int type = originalImage.getType() == 0 ? BufferedImage.TYPE_INT_ARGB : originalImage.getType();
                int width = originalImage.getWidth();
                int height = originalImage.getHeight();
                //System.out.println("width:" + width + " height:" + height);
                int width_new;
                int height_new;
                if (width > height) {
                    if (width > max_size) {
                        width_new = max_size;
                        double ratio = (double) (((double) width) / ((double) max_size));
                        height_new = (int) ((double) (height / ratio));
                    } else {
                        width_new = width;
                        height_new = height;
                    }
                } else {
                    if (height > max_size) {
                        height_new = max_size;
                        double ratio = (double) (((double) height) / ((double) max_size));
                        //System.out.println("ratio:" + ratio);
                        width_new = (int) ((double) (width / ratio));
                    } else {
                        width_new = width;
                        height_new = height;
                    }
                }
                //System.out.println("width_new:" + width_new + " height_new:" + height_new);
                BufferedImage resizeImageHintJpg = resizeImageWithHint(originalImage, type, width_new, height_new);
                ImageIO.write(resizeImageHintJpg, "jpg", new File(new_path + DIV_DIRECTORY + name + "_" + i + ".jpg"));
            } catch (IOException e) {
                System.out.println(e.getMessage());
            }
        }
    }

    public static void resizeImagesFromFolder(GUI frame, String folder, String name, int max_size) {
        String[] list;
        String new_path = folder + name;
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
        list = Find.getImagesInFolder(folder);
        for (int i = 0; i < list.length; i++) {
            try {
                BufferedImage originalImage = ImageIO.read(new File(folder + list[i]));
                int type = originalImage.getType() == 0 ? BufferedImage.TYPE_INT_ARGB : originalImage.getType();
                int width = originalImage.getWidth();
                int height = originalImage.getHeight();
                frame.setTextArea("[" + i + "] reading image" + " width:" + width + " height:" + height + " name:" + list[i]);
                //System.out.println("width:" + width + " height:" + height);
                int width_new;
                int height_new;
                if (width > height) {
                    if (width > max_size) {
                        width_new = max_size;
                        double ratio = (double) (((double) width) / ((double) max_size));
                        height_new = (int) ((double) (height / ratio));
                    } else {
                        width_new = width;
                        height_new = height;
                    }
                } else {
                    if (height > max_size) {
                        height_new = max_size;
                        double ratio = (double) (((double) height) / ((double) max_size));
                        //System.out.println("ratio:" + ratio);
                        width_new = (int) ((double) (width / ratio));
                    } else {
                        width_new = width;
                        height_new = height;
                    }
                }
                //System.out.println("width_new:" + width_new + " height_new:" + height_new);
                BufferedImage resizeImageHintJpg = resizeImageWithHint(originalImage, type, width_new, height_new);
                String new_name = name + "_" + i + ".jpg";
                frame.setTextArea("  writing image width:" + width_new + " height:" + height_new + " name:" + new_name);
                ImageIO.write(resizeImageHintJpg, "jpg", new File(new_path + DIV_DIRECTORY + new_name));
            } catch (IOException e) {
                System.out.println(e.getMessage());
                frame.setTextArea(e.getMessage());
            }
        }
    }

    private static BufferedImage resizeImage(BufferedImage originalImage, int type) {
        BufferedImage resizedImage = new BufferedImage(IMG_WIDTH, IMG_HEIGHT, type);
        Graphics2D g = resizedImage.createGraphics();
        g.drawImage(originalImage, 0, 0, IMG_WIDTH, IMG_HEIGHT, null);
        g.dispose();

        return resizedImage;
    }

    private static BufferedImage resizeImageWithHint(BufferedImage originalImage, int type) {

        BufferedImage resizedImage = new BufferedImage(IMG_WIDTH, IMG_HEIGHT, type);
        Graphics2D g = resizedImage.createGraphics();
        g.drawImage(originalImage, 0, 0, IMG_WIDTH, IMG_HEIGHT, null);
        g.dispose();
        g.setComposite(AlphaComposite.Src);

        g.setRenderingHint(RenderingHints.KEY_INTERPOLATION,
                RenderingHints.VALUE_INTERPOLATION_BILINEAR);
        g.setRenderingHint(RenderingHints.KEY_RENDERING,
                RenderingHints.VALUE_RENDER_QUALITY);
        g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);

        return resizedImage;
    }

    private static BufferedImage resizeImageWithHint(BufferedImage originalImage, int type, int width, int height) {

        BufferedImage resizedImage = new BufferedImage(width, height, type);
        Graphics2D g = resizedImage.createGraphics();
        g.drawImage(originalImage, 0, 0, width, height, null);
        g.dispose();
        g.setComposite(AlphaComposite.Src);

        g.setRenderingHint(RenderingHints.KEY_INTERPOLATION,
                RenderingHints.VALUE_INTERPOLATION_BILINEAR);
        g.setRenderingHint(RenderingHints.KEY_RENDERING,
                RenderingHints.VALUE_RENDER_QUALITY);
        g.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);

        return resizedImage;
    }

    public static void main(String[] args) {

        try {

            BufferedImage originalImage = ImageIO.read(new File("C:\\CUDA\\pic\\resize_test\\001.jpg"));
            int type = originalImage.getType() == 0 ? BufferedImage.TYPE_INT_ARGB : originalImage.getType();

//            BufferedImage resizeImageJpg = resizeImage(originalImage, type);
//            ImageIO.write(resizeImageJpg, "jpg", new File("C:\\CUDA\\pic\\resize_test\\001_resize.jpg"));
//
//            BufferedImage resizeImagePng = resizeImage(originalImage, type);
//            ImageIO.write(resizeImagePng, "png", new File("c:\\image\\mkyong_png.jpg"));
            BufferedImage resizeImageHintJpg = resizeImageWithHint(originalImage, type);
            ImageIO.write(resizeImageHintJpg, "jpg", new File("C:\\CUDA\\pic\\resize_test\\001_hint_resize.jpg"));

            Resize.resizeImagesFromFolder("C:\\CUDA\\pic\\resize_test\\set\\", "back", 150);
//            BufferedImage resizeImageHintPng = resizeImageWithHint(originalImage, type);
//            ImageIO.write(resizeImageHintPng, "png", new File("c:\\image\\mkyong_hint_png.jpg"));
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

    }
}
