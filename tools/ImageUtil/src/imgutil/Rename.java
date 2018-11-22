/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package imgutil;

import constants.Constant;
import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

/**
 *
 * @author alex
 */
public class Rename implements Constant{

    public static void copyFile(File sourceFile, File destFile) throws IOException {
        if (!destFile.exists()) {
            destFile.createNewFile();
        }

        FileChannel source = null;
        FileChannel destination = null;
        try {
            source = new RandomAccessFile(sourceFile, "rw").getChannel();
            destination = new RandomAccessFile(destFile, "rw").getChannel();

            long position = 0;
            long count = source.size();

            source.transferTo(position, count, destination);
        } finally {
            if (source != null) {
                source.close();
            }
            if (destination != null) {
                destination.close();
            }
        }
    }

    public static void renameFilesFromFolder(String folder, String name) {
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
        list = Find.getFilesInFolder(folder);
        for (int i = 0; i < list.length; i++) {
            String[] fls = list[i].split("\\.");
            String ext = fls[1];
            File source = new File(folder + list[i]);
            File destination = new File(new_path + DIV_DIRECTORY + name + "_" + i + "." + ext);
            try {
                copyFile(source, destination);
            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }
    
    public static void main(String[] args){
        String folder = "C:\\CUDA\\pic\\UCMerced_LandUse\\UCMerced_LandUse\\temp\\";  // for windows
        renameFilesFromFolder(folder, "test");
    }
}
