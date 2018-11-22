/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package utils;


/**
 *
 * @author ratsaby
 * Convenience class, wrapper of byte[], which represents a sequence of characters (for instance from a gray scale image)
 * 
 * 
 */
public class Sequence {
 
    
    private byte[] bytes;
    private String name; // used to store file name of the image that this sequence represents
    
    
    public Sequence(byte[] b) {
        bytes=b;
        
        
    }
    
    public Sequence(byte[] b, String n) {
       name = n; 
       bytes=b;
    }
    
    /**
     * Used for purpose of multi tread, since I dont want static method concatenate so I first build object and run this method on object
     * which allows concurrent threads to run it
     */
    public Sequence() {
        
    }
    
    
    
    public byte[] bytes() {
        return bytes;
    }
    
    
    /*
    public static Sequence concatenate(Sequence s1, Sequence s2) {
        
        byte[] bytes1 = s1.bytes();
        byte[] bytes2=  s2.bytes();
        
        byte[] concat = new byte[bytes1.length+bytes2.length];
        
        System.arraycopy(bytes1, 0, concat, 0, bytes1.length);
        System.arraycopy(bytes2, 0, concat, bytes1.length, bytes2.length);
        
        return new Sequence(concat);
    }
    
    */
    
    public String name() {
        return name;
    }
    
    public void   concatenate(Sequence s1, Sequence s2) {
        
        byte[] bytes1 = s1.bytes();
        byte[] bytes2=  s2.bytes();
        
        
        
        
        bytes = new byte[bytes1.length + bytes2.length];
        
        
        for(int i=0; i< bytes1.length;i++)
            bytes[i]=bytes1[i];

        for(int i= 0; i< bytes2.length; i++)
            bytes[i+bytes1.length]=bytes2[i];
    }
 
}
