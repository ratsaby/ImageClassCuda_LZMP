/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package imgutil;

import java.io.File;
import java.util.Arrays;
import java.util.Vector;

/**
 *
 * @author alex
 */
public class Find {

    public static String[] getImagesInFolder(String folder) {
        File f = new File(folder);

        Vector<String> list = new Vector<String>();
        File names[] = f.listFiles();
        for (int i = 0; i < names.length; i++) {
            if (names[i].isFile()) {
                String s = names[i].getName();
                System.out.println("[" + i + "]" + "name:" + s);
                String s1 = s.toUpperCase();
                if (s1.lastIndexOf(".JPG") > 0) {
                    list.add(s);
                }
            }
        }
        // let us order the array
        Object[] names1 = list.toArray();
        Arrays.sort(names1);
        String[] names2 = new String[names1.length];
        for (int i = 0; i < names2.length; i++) {
            names2[i] = (String) names1[i];
        }
        return names2;
    }

    public static String[] getFilesInFolder(String folder) {
        File f = new File(folder);

        Vector<String> list = new Vector<String>();
        File names[] = f.listFiles();
        for (int i = 0; i < names.length; i++) {
            if (names[i].isFile()) {
                String s = names[i].getName();
                System.out.println("[" + i + "]" + "name:" + s);
                String s1 = s.toUpperCase();
                list.add(s);
            }
        }
        // let us order the array
        Object[] names1 = list.toArray();
        Arrays.sort(names1);
        String[] names2 = new String[names1.length];
        for (int i = 0; i < names2.length; i++) {
            names2[i] = (String) names1[i];
        }
        return names2;
    }

    public static void main(String[] args) {
        String folder = "C:/CUDA/pic/UCMerced_LandUse/UCMerced_LandUse/Images/agricultural/";
        String[] files_name = Find.getFilesInFolder(folder);
    }
}
