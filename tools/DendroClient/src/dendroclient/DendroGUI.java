/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dendroclient;

import com.apporiented.algorithm.clustering.visualization.DendrogramPanel;
import constants.Constants;
import static constants.Constants.myFormatterDoub;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.StringTokenizer;
import javax.swing.JOptionPane;
import static javax.swing.JOptionPane.ERROR_MESSAGE;
import javax.swing.filechooser.FileNameExtensionFilter;
import table.Table;
import utils.Sequence;

/**
 *
 * @author alex
 */
public class DendroGUI extends javax.swing.JFrame implements Constants {

    private javax.swing.JFileChooser jFileChooser1;
    FileNameExtensionFilter fileFilterImport = new FileNameExtensionFilter(".txt", "txt");

    private javax.swing.JFileChooser jFileChooser2;
    FileNameExtensionFilter fileFilterExport = new FileNameExtensionFilter(".xlsx", "xlsx");

    static double protoDistMatrix[][];

    //static Sequence[] images;
    static String[] images;
    //static String[] labels;  // the labels of the above images
    static String[] categories;
    /**
     * Creates new form Dendro
     */
    public DendroGUI() {
        initComponents();
        my_init();
    }

    private void my_init() {

        jFileChooser1 = new javax.swing.JFileChooser();
        //jFileChooser1.setFont(new java.awt.Font("Arial", 0, 11));
        jFileChooser1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jFileChooser1ActionPerformed(evt);
            }
        });
    }

    private void jFileChooser1ActionPerformed(java.awt.event.ActionEvent evt) {
        System.out.println("evt.getActionCommand():" + evt.getActionCommand());
        if (evt.getActionCommand() == "ApproveSelection") {
            importDistFile(jFileChooser1.getSelectedFile());
        }
    }

    private void importDistFile(File f) {
        System.out.println("Will read the matrix from file: " + f.getAbsolutePath());

        //File f = new File(WindowsOS.prepareFileName(pathToFile));
        FileReader fw = null;
        try {
            fw = new FileReader(f);
        } catch (Exception e) {
            System.out.println("Could not open  file !");
            System.out.println(e.toString());
            e.printStackTrace(System.out);
            JOptionPane.showMessageDialog(jFileChooser1, e.getLocalizedMessage(), "Open dialog", ERROR_MESSAGE);
        }
        BufferedReader bufw = new BufferedReader(fw);//just for efficiency

        String l;
        String title = null;
        //double array[][] = null;
        int n = 0;
        try {
            int row = 0;
            title = bufw.readLine();   // first line is a Title
            StringTokenizer stlb = new StringTokenizer(bufw.readLine()); // second is a labels
            images = new String[stlb.countTokens()];
            for(int i = 0; i < images.length; i++){
                images[i] = stlb.nextToken();
                System.out.println(images[i]);
            }
            StringTokenizer stcateg = new StringTokenizer(bufw.readLine()); // third is a category
            categories = new String[stcateg.countTokens()];
            for(int i = 0; i < categories.length; i++){
                categories[i] = stcateg.nextToken();
                System.out.println(categories[i]);
            }
            while ((l = bufw.readLine()) != null) {
                StringTokenizer st = new StringTokenizer(l);
                n = st.countTokens(); // get number of tokens = numb of cols

                if (row == 0) {
                    protoDistMatrix = new double[n][n]; // the distance matrix is square. we only build array at start
                }
                int col = 0;
                while (st.hasMoreTokens()) {
                    protoDistMatrix[row][col] = Double.parseDouble(st.nextToken());
                    col++;
                }
                System.out.println("Row# " + row + ":" + l);
                row++;
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
            if (e.getMessage() != null) {
                JOptionPane.showMessageDialog(jFileChooser1, e.getLocalizedMessage(), "Open dialog", ERROR_MESSAGE);
            }
        }
        System.out.println("\nFinished reading distance matrix from file... \n\n");
        displayDistTable();
        DendrogramPanel.buildDendogramForGivenArray(protoDistMatrix, HIERAR_CLUSTER_METHOD, title);
//        try {
//            String content = new Scanner(f).useDelimiter("\\Z").next();
//            System.out.println(content);
//            String[] strRow = content.split("\n");
//            int row = strRow.length;
//            String[] strCol = strRow[0].split(",");
//            int col = strCol.length;
//            
//            System.out.println("num of row:" + row + "num of col:" + col);
//            
//            decodeDistanceMatFromString(content);
//        } catch (Exception e) {
//            System.out.println(e.getMessage());
//            if (e.getMessage() != null) {
//                JOptionPane.showMessageDialog(jFileChooser1, e.getLocalizedMessage(), "Open dialog", ERROR_MESSAGE);
//            }
//        }
    }

    private static void displayDistTable() {
        Object[] stuff = util1();
        Table.createAndShowTable("DistanceMatrix", (Object[][]) stuff[0], (String[]) stuff[1]);
    }

    private static Object[] util1() {
        Object[][] proto = new Object[images.length + 1][images.length + 2];//add two more column (first one) to display row names, second the prototype names. 
        // add one more row, first to display prototype names
        for (int i = 0; i < images.length + 1; i++) {
            for (int j = 0; j < images.length + 2; j++) {
                if (j == 0) {
                    if (i == 0) {
                        proto[i][j] = "";
                    } else {
                        proto[i][j] = categories[i - 1]; // category
                    }
                } else if (j == 1) {
                    if (i == 0) {
                        proto[i][j] = "Prototype";
                    } else {
                        proto[i][j] = Integer.toString(i)+" ("+images[i-1] +")"; // prototype #, starting from 1,2,3....
                    }
                } else {
                    if (i == 0) {
                        proto[i][j] = Integer.toString(j - 1)+" ("+images[j-2] +")"; // the prototype #, starting from 1,2,3....
                    } else {
                        String d = myFormatterDoub.format(protoDistMatrix[i - 1][j - 2]);
                        proto[i][j] = d;
                    }
                }
            }
        }
        String[] names = new String[categories.length + 2];
        names[0] = "Category";
        names[1] = "";
        System.arraycopy(categories, 0, names, 2, categories.length);
        Object[] protoAndNames = new Object[2];
        protoAndNames[0] = proto;
        protoAndNames[1] = names;
        return protoAndNames;
    }
    
    private void decodeDistanceMatFromString(String str) {

//        protoDistMatrix = new double[3][3];
//        protoDistMatrix[0][0] = 0;
//        protoDistMatrix[0][1] = 1;
//        protoDistMatrix[0][2] = 2;
//
//        protoDistMatrix[1][0] = 3;
//        protoDistMatrix[1][1] = 0;
//        protoDistMatrix[1][2] = 4;
//
//        protoDistMatrix[2][0] = 1;
//        protoDistMatrix[2][1] = 3;
//        protoDistMatrix[2][2] = 0;
//
//        DendrogramPanel.buildDendogramForGivenArray(protoDistMatrix, HIERAR_CLUSTER_METHOD);
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jMenuBar1 = new javax.swing.JMenuBar();
        jMenu1 = new javax.swing.JMenu();
        jMenuItem1 = new javax.swing.JMenuItem();
        jMenu2 = new javax.swing.JMenu();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("DendroClient - v1.0");

        jLabel1.setFont(new java.awt.Font("Ubuntu", 1, 14)); // NOI18N
        jLabel1.setText("Dendrogram from distance matrix");

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(91, 91, 91)
                .addComponent(jLabel1)
                .addContainerGap(117, Short.MAX_VALUE))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(16, 16, 16)
                .addComponent(jLabel1)
                .addContainerGap(21, Short.MAX_VALUE))
        );

        jMenu1.setText("File");

        jMenuItem1.setText("Import Distance matrix");
        jMenuItem1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jMenuItem1ActionPerformed(evt);
            }
        });
        jMenu1.add(jMenuItem1);

        jMenuBar1.add(jMenu1);

        jMenu2.setText("Edit");
        jMenuBar1.add(jMenu2);

        setJMenuBar(jMenuBar1);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void jMenuItem1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jMenuItem1ActionPerformed
        jFileChooser1.setAcceptAllFileFilterUsed(false);
        jFileChooser1.addChoosableFileFilter(fileFilterImport);
        jFileChooser1.showOpenDialog(DendroGUI.this);
    }//GEN-LAST:event_jMenuItem1ActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(DendroGUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(DendroGUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(DendroGUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(DendroGUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new DendroGUI().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel jLabel1;
    private javax.swing.JMenu jMenu1;
    private javax.swing.JMenu jMenu2;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JMenuItem jMenuItem1;
    private javax.swing.JPanel jPanel1;
    // End of variables declaration//GEN-END:variables
}
