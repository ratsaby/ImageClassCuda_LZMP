/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package utils;

/**
 *
 * @author ratsaby
 */
public class SingleLearningCase {

    String inputImageFileName; // this is the image file in the folder 3. InputImageFolder which corresponds to this single Learning Case
    String classAttr;

    double[] values; // of the case

    public String getClassAttr() {
        return classAttr;
    }

    public SingleLearningCase(String s) {
        inputImageFileName = s;
        determineClassAttr(s);
    }

    public void setValues(double[] c) {
        values = c;
    }

    public double[] getValues() {
        return values;
    }

    public String getName() {
        return inputImageFileName;
    }

    public void setClassAttribute(String s) {
        classAttr = s;
    }

    
    private void determineClassAttr(String name) {
     
        try{
       classAttr = name.substring(0, name.indexOf("_"));// the category name is string before _   in the file name
        } catch (IndexOutOfBoundsException  ex) {
            System.out.println("Problem in name of Image file !! You should have an underscor _ after categoryname: For example:   CATEG1_IMG12.jpg  ");

            System.exit(1);
        }
        
    }
    
}
