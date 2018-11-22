package constants;

import java.text.DecimalFormat;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author ratsaby
 */
public interface Constants {

    enum OSType {

        Windows,
        Mac,
        Linux; // this means ;
    }
    
    
     enum CalcType {

        UIDistance,
        Other;
    }
    final OSType OS = OSType.Linux;
    static final String dirName = (OS == OSType.Linux ? "/home/ratsaby/Documents/ImageRuns/" : (OS == OSType.Windows ? "C:\\ImageRuns\\" : "/Users/ratsaby/Documents/Imageruns/"));
    /**
     * This enables all messages via Service.errPrint() to go to the Log.dat
     * file under the {@link #dirName dirName}
     */
    final static boolean LOG = true;
    
    
    final static boolean ORIG_IS_MATLAB = false; // if true, then original images are in MAT format (matlab matrix, as in Boris' data), otherwise it is in COLOR JPG
    final static int MAT_FILE_W_RESOLUTION = 20; // the number of pixels we wish the WIDTH of the JPG that is formed from conversion of the MAT file
    final static int MAT_FILE_H_RESOLUTION = 20; // the number of pixels we wish the WIDTH of the JPG that is formed from conversion of the MAT file
    
    
    
    
    //final public String dirName = "/home/ratsaby/NetBeansProjects/MyImageAlgo/";
    final static public String unlabeledPrototypes = "1. UnlabImagePrototypes";
    final static public String tempDir = "Temp";
    final static public String labeledPrototypes = "2. LabImagePrototypes";
    final static public String inputImageFolder = "3. InputImageFolder";
    final static public String casesFolder = "4. LearningCases";
    
    final static public byte TEST = 2;// the higher the number the more verbose .
 
    
    final static public boolean ARTIFICIAL_IMAGES_FOR_TESTING = false; // causes creation of artificial image data (rather than reading real images)
    
    
    final static public String patternDouble1 = "0.#####"; // "#00.0"; 
    final static public DecimalFormat myFormatterDoub = new DecimalFormat(patternDouble1);
    final static public char HIERAR_CLUSTER_METHOD = 's'; // linking type (see method buildDendogramForGivenArray)
    final static public short NUMB_SUB_IMAGES = 2; // this is the # of subimages that a picture is split up into
    
    final  static String EXT = ".dat"; // extension used for all files 
    static String EXT_IMG="JPG"; // extension of img files
    final static public String FILE_DIST_MATRX = "DistMatrix"+EXT;
    
    
    
   /**  
    * 
    * path to the output directory
    * 
    * (Java allows for 'space' to be in the file name)
    * 
    * 
    */
static  final String pathReport = "Report";

    final public static  CalcType CALCULATION_TYPE=CalcType.UIDistance;

    static  final int NUMB_THREADS = 1;

final public static boolean SAVE_DISK_ACCESS_TO_SPEED_UP = true;
final public static boolean MEMORY_CLEAN = false;



  enum DistanceModeType { /** controls way distance between subimage and prototype is computed in {@link algorithms.Algorithm3#step4_5() step4_5} */

        StandardEuclidean, /** just as in the SISAP paper, use this when {@link #NUMB_SUB_IMAGES NUMB_SUB_IMAGES} is large, say larger than 4. */
        UsingDistanceFromPrototypesInsteadOfCounts, /**  Use this if want array {@link algorithms.Algorithm3#counts counts} to hold distances to all prototypes rather than the frequency   */
        ExplicitProtoDistInCase; /**  use this when {@link #NUMB_SUB_IMAGES NUMB_SUB_IMAGES} is small, say smaller than 4.  */
    }
    
    final DistanceModeType DistType = DistanceModeType.StandardEuclidean;

}




