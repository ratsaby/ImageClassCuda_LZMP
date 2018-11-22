/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package utils;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *
 * @author ratsaby
 */
public class WindowsOS {

    /**
     * Removes the chars that are not allowed under the Windows OS
     * @param s
     */
    public static String prepareFileName(String s) {
        
        String temp = new String(s);

        Pattern p = Pattern.compile("[*./:;|=,]");
        Matcher m = p.matcher(temp);
       temp =  m.replaceAll("_");
        
        return temp;
        
    }
    
    
}
