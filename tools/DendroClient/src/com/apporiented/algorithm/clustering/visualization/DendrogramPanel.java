/**
 * *****************************************************************************
 * Copyright 2013 Lars Behnke
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 *****************************************************************************
 */
package com.apporiented.algorithm.clustering.visualization;

import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.geom.Rectangle2D;

import javax.swing.JFrame;
import javax.swing.JPanel;

import com.apporiented.algorithm.clustering.AverageLinkageStrategy;
import com.apporiented.algorithm.clustering.Cluster;
import com.apporiented.algorithm.clustering.ClusteringAlgorithm;
import com.apporiented.algorithm.clustering.CompleteLinkageStrategy;
import com.apporiented.algorithm.clustering.DefaultClusteringAlgorithm;
import com.apporiented.algorithm.clustering.LinkageStrategy;
import com.apporiented.algorithm.clustering.SingleLinkageStrategy;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *
 * @author ratsaby
 *
 * either run fro command line like: java
 * com.apporiented.algorithm.clustering.visualization.DendrogramPanel <filename>
 * <s/a/c>
 * where file name is as specified in the main method below.
 *
 *
 * Or just call the method buildDendogramForGivenArray(double[][] array, char
 * sel) below
 *
 */
public class DendrogramPanel extends JPanel {

    private static final long serialVersionUID = 1L;

    final static BasicStroke solidStroke = new BasicStroke(1.0f, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND);

    private Cluster model;
    private ClusterComponent component;
    private Color lineColor = Color.BLACK;
    private boolean showDistanceValues = false;
    private boolean showScale = true;
    private int borderTop = 20;
    private int borderLeft = 20;
    private int borderRight = 20;
    private int borderBottom = 20;
    private int scalePadding = 10;
    private int scaleTickLength = 4;
    private int scaleTickLabelPadding = 4;
    private double scaleValueInterval = 0;
    private int scaleValueDecimals = 0;

    private double xModelOrigin = 0.0;
    private double yModelOrigin = 0.0;
    private double wModel = 0.0;
    private double hModel = 0.0;

    public boolean isShowDistanceValues() {
        return showDistanceValues;
    }

    public void setShowDistances(boolean showDistanceValues) {
        this.showDistanceValues = showDistanceValues;
    }

    public boolean isShowScale() {
        return showScale;
    }

    public void setShowScale(boolean showScale) {
        this.showScale = showScale;
    }

    public int getScalePadding() {
        return scalePadding;
    }

    public void setScalePadding(int scalePadding) {
        this.scalePadding = scalePadding;
    }

    public int getScaleTickLength() {
        return scaleTickLength;
    }

    public void setScaleTickLength(int scaleTickLength) {
        this.scaleTickLength = scaleTickLength;
    }

    public double getScaleValueInterval() {
        return scaleValueInterval;
    }

    public void setScaleValueInterval(double scaleTickInterval) {
        this.scaleValueInterval = scaleTickInterval;
    }

    public int getScaleValueDecimals() {
        return scaleValueDecimals;
    }

    public void setScaleValueDecimals(int scaleValueDecimals) {
        this.scaleValueDecimals = scaleValueDecimals;
    }

    public int getBorderTop() {
        return borderTop;
    }

    public void setBorderTop(int borderTop) {
        this.borderTop = borderTop;
    }

    public int getBorderLeft() {
        return borderLeft;
    }

    public void setBorderLeft(int borderLeft) {
        this.borderLeft = borderLeft;
    }

    public int getBorderRight() {
        return borderRight;
    }

    public void setBorderRight(int borderRight) {
        this.borderRight = borderRight;
    }

    public int getBorderBottom() {
        return borderBottom;
    }

    public void setBorderBottom(int borderBottom) {
        this.borderBottom = borderBottom;
    }

    public Color getLineColor() {
        return lineColor;
    }

    public void setLineColor(Color lineColor) {
        this.lineColor = lineColor;
    }

    public Cluster getModel() {
        return model;
    }

    public void setModel(Cluster model) {
        this.model = model;
        component = createComponent(model);
        updateModelMetrics();
    }

    private void updateModelMetrics() {
        double minX = component.getRectMinX();
        double maxX = component.getRectMaxX();
        double minY = component.getRectMinY();
        double maxY = component.getRectMaxY();

        xModelOrigin = minX;
        yModelOrigin = minY;
        wModel = maxX - minX;
        hModel = maxY - minY;
    }

    private ClusterComponent createComponent(Cluster cluster, VCoord initCoord, double clusterHeight) {

        ClusterComponent comp = null;
        if (cluster != null) {
            comp = new ClusterComponent(cluster, cluster.isLeaf(), initCoord);
            double leafHeight = clusterHeight / cluster.countLeafs();
            double yChild = initCoord.getY() - (clusterHeight / 2);
            double distance = cluster.getDistance() == null ? 0 : cluster.getDistance();
            for (Cluster child : cluster.getChildren()) {
                int childLeafCount = child.countLeafs();
                double childHeight = childLeafCount * leafHeight;
                double childDistance = child.getDistance() == null ? 0 : child.getDistance();
                VCoord childInitCoord = new VCoord(initCoord.getX() + (distance - childDistance), yChild + childHeight
                        / 2.0);
                yChild += childHeight;

                /* Traverse cluster node tree */
                ClusterComponent childComp = createComponent(child, childInitCoord, childHeight);

                childComp.setLinkPoint(initCoord);
                comp.getChildren().add(childComp);
            }
        }
        return comp;

    }

    private ClusterComponent createComponent(Cluster model) {

        double virtualModelHeight = 1;
        VCoord initCoord = new VCoord(0, virtualModelHeight / 2);

        ClusterComponent comp = createComponent(model, initCoord, virtualModelHeight);
        comp.setLinkPoint(initCoord);
        return comp;
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        g2.setColor(lineColor);
        g2.setStroke(solidStroke);

        int wDisplay = getWidth() - borderLeft - borderRight;
        int hDisplay = getHeight() - borderTop - borderBottom;
        int xDisplayOrigin = borderLeft;
        int yDisplayOrigin = borderBottom;

        if (component != null) {

            int nameGutterWidth = component.getMaxNameWidth(g2, false) + component.getNamePadding();
            wDisplay -= nameGutterWidth;

            if (showScale) {
                Rectangle2D rect = g2.getFontMetrics().getStringBounds("0", g2);
                int scaleHeight = (int) rect.getHeight() + scalePadding + scaleTickLength + scaleTickLabelPadding;
                hDisplay -= scaleHeight;
                yDisplayOrigin += scaleHeight;
            }

            /* Calculate conversion factor and offset for display */
            double xFactor = wDisplay / wModel;
            double yFactor = hDisplay / hModel;
            int xOffset = (int) (xDisplayOrigin - xModelOrigin * xFactor);
            int yOffset = (int) (yDisplayOrigin - yModelOrigin * yFactor);
            component.paint(g2, xOffset, yOffset, xFactor, yFactor, showDistanceValues);

            if (showScale) {
                int x1 = xDisplayOrigin;
                int y1 = yDisplayOrigin - scalePadding;
                int x2 = x1 + wDisplay;
                int y2 = y1;
                g2.drawLine(x1, y1, x2, y2);

                double totalDistance = component.getCluster().getTotalDistance();
                double xModelInterval;
                if (scaleValueInterval <= 0) {
                    xModelInterval = totalDistance / 10.0;
                } else {
                    xModelInterval = scaleValueInterval;
                }

                int xTick = xDisplayOrigin + wDisplay;
                y1 = (int) (yDisplayOrigin - scalePadding);
                y2 = (int) (yDisplayOrigin - scalePadding - scaleTickLength);
                double distanceValue = 0;
                double xDisplayInterval = xModelInterval * xFactor;
                while (xTick >= xDisplayOrigin) {
                    g2.drawLine(xTick, y1, xTick, y2);

                    String distanceValueStr = String.format("%." + scaleValueDecimals + "f", distanceValue);
                    Rectangle2D rect = g2.getFontMetrics().getStringBounds(distanceValueStr, g2);
                    g2.drawString(distanceValueStr, (int) (xTick - (rect.getWidth() / 2)), y2 - scaleTickLabelPadding);
                    xTick -= xDisplayInterval;
                    distanceValue += xModelInterval;
                }

            }
        } else {

            /* No data available */
            String str = "No data";
            Rectangle2D rect = g2.getFontMetrics().getStringBounds(str, g2);
            int xt = (int) (wDisplay / 2.0 - rect.getWidth() / 2.0);
            int yt = (int) (hDisplay / 2.0 - rect.getHeight() / 2.0);
            g2.drawString(str, xt, yt);
        }
    }

    /*
     public static void main(String[] args) {
     JFrame frame = new JFrame();
     frame.setSize(400, 300);
     frame.setLocation(400, 300);
     frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

     JPanel content = new JPanel();
     DendrogramPanel dp = new DendrogramPanel();

     frame.setContentPane(content);
     content.setBackground(Color.red);
     content.setLayout(new BorderLayout());
     content.add(dp, BorderLayout.CENTER);
     dp.setBackground(Color.WHITE);
     dp.setLineColor(Color.BLACK);
     dp.setScaleValueDecimals(0);
     dp.setScaleValueInterval(1);
     dp.setShowDistances(false);

     //Cluster cluster = createSampleCluster();
     Cluster cluster = createSampleClusterJoel();
     dp.setModel(cluster);
     frame.setVisible(true);
     }
     */
    /**
     * Main (by Joel)
     *
     * @param args[0] FileName contains the distance matrix in space separated
     * elements, and Newline for separating rows
     * @param args[1] single character: s for single, a for average, c for
     * complete, linking strategy
     */
    public static void main(String[] args) {

        String pathToFile = args[0];
        char sel = args[1].charAt(0);

        System.out.println("Will read the matrix from file: " + pathToFile);

        //File f = new File(WindowsOS.prepareFileName(pathToFile));
        File f = new File(pathToFile);
        FileReader fw = null;
        try {
            fw = new FileReader(f);
        } catch (Exception e) {
            System.out.println("Could not open  file !");
            System.out.println(e.toString());
            e.printStackTrace(System.out);
        }
        BufferedReader bufw = new BufferedReader(fw);//just for efficiency

        String l;
        double array[][] = null;
        int n = 0;
        try {
            int row = 0;

            while ((l = bufw.readLine()) != null) {
                StringTokenizer st = new StringTokenizer(l);
                n = st.countTokens(); // get number of tokens = numb of cols

                if (row == 0) {
                    array = new double[n][n]; // the distance matrix is square. we only build array at start
                }
                int col = 0;
                while (st.hasMoreTokens()) {
                    array[row][col] = Double.parseDouble(st.nextToken());
                    col++;
                }
                System.out.println("Row# " + row + ":" + l);
                row++;
            }
        } catch (Exception e) {
        }
        System.out.println("\nFinished reading distance matrix from file... \n\n");

        JFrame frame = new JFrame();
        frame.setSize(400, 300);
        frame.setLocation(400, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel content = new JPanel();
        DendrogramPanel dp = new DendrogramPanel();

        frame.setContentPane(content);
        content.setBackground(Color.red);
        content.setLayout(new BorderLayout());
        content.add(dp, BorderLayout.CENTER);
        dp.setBackground(Color.WHITE);
        dp.setLineColor(Color.BLACK);
        dp.setScaleValueDecimals(0);
        dp.setScaleValueInterval(1);
        dp.setShowDistances(false);

        //Cluster cluster = createSampleCluster();
        // Cluster cluster = createSampleClusterJoel();
        Cluster cluster = createSampleClusterFromMatrixJoel(n, array, sel);
        dp.setModel(cluster);
        frame.setVisible(true);
    }

    /**
     *
     * @param array given data to cluster (distance matrix)
     * @param sel single character: 's' for single, 'a' for average, 'c' for
     * complete, linking strategy
     */
    public static void buildDendogramForGivenArray(double[][] array, char sel, String title) {

        JFrame frame = new JFrame();
        frame.setSize(400, 300);
        frame.setLocation(400, 300);
        frame.setTitle(title);
        //frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel content = new JPanel();
        DendrogramPanel dp = new DendrogramPanel();

        frame.setContentPane(content);
        content.setBackground(Color.red);
        content.setLayout(new BorderLayout());
        content.add(dp, BorderLayout.CENTER);
        dp.setBackground(Color.WHITE);
        dp.setLineColor(Color.BLACK);
        dp.setScaleValueDecimals(0);
        dp.setScaleValueInterval(1);
        dp.setShowDistances(false);

        int n = array[0].length; // number of columns 
        //Cluster cluster = createSampleCluster();
        // Cluster cluster = createSampleClusterJoel();
        Cluster cluster = createSampleClusterFromMatrixJoel(n, array, sel);
        dp.setModel(cluster);
        frame.setVisible(true);

    }
        
    private static Cluster createSampleCluster() {
        double[][] distances = new double[][]{{0, 1, 9, 7, 11, 14}, {1, 0, 4.8, 3, 8, 10}, {9, 4, 0, 9, 2, 8},
        {7, 3, 9, 0, 6, 13}, {11, 8, 2, 6, 0, 10}, {14, 10, 8, 13, 10, 0}};
        String[] names = new String[]{"O1", "O2", "O3", "O4", "O5", "O6"};
        ClusteringAlgorithm alg = new DefaultClusteringAlgorithm();

        Cluster cluster = alg.performClustering(distances, names, new AverageLinkageStrategy());
        cluster.toConsole(0);
        return cluster;
    }

    private static Cluster createSampleClusterJoel() {
        double[][] distances = new double[][]{
            {0, 0.882767456758488, 0.901985906470211, 0.998078155028828, 0.979500320307495, 0.998718770019219, 0.903907751441384, 0.918641896220372, 0.922485586162716, 0.967328635490070, 0.980140935297886, 0.974375400384369},
            {0.880204996796925, 0, 0.879689521345408, 0.998706338939198, 0.983829236739974, 0.998706338939198, 0.897800776196637, 0.906209573091850, 0.908796895213454, 0.967658473479948, 0.979301423027167, 0.974126778783959},
            {0.892376681614350, 0.870633893919793, 0, 1, 0.994148244473342, 1, 0.920026007802341, 0.921976592977893, 0.927178153446034, 0.951235370611183, 0.961638491547464, 0.953185955786736},
            {0.995515695067265, 0.996119016817594, 0.999349804941482, 0.00117096018735363, 0.914839797639123, 0.923887587822014, 0.985887096774194, 0.992565055762082, 0.980337078651685, 1, 1, 1},
            {0.977578475336323, 0.980595084087969, 0.992197659297789, 0.933389544688027, 0.000843170320404722, 0.983979763912310, 0.941532258064516, 0.947211895910781, 0.926264044943820, 1, 1, 1},
            {0.991672005124920, 0.992884864165589, 0.997399219765930, 0.907494145199063, 0.961214165261383, 0, 0.981854838709677, 0.988847583643123, 0.974016853932584, 1, 1, 1},
            {0.901985906470211, 0.889391979301423, 0.928478543563069, 0.988575268817204, 0.948924731182796, 0.997311827956989, 0.000672043010752688, 0.880376344086022, 0.870967741935484, 0.979838709677419, 0.990591397849462, 0.987903225806452},
            {0.911595131326073, 0.900388098318241, 0.927828348504551, 0.996282527881041, 0.951672862453532, 0.999256505576208, 0.878360215053764, 0.000743494423791822, 0.868679775280899, 0.980669144981413, 0.992565055762082, 0.991821561338290},
            {0.910313901345291, 0.899094437257439, 0.942782834850455, 0.984550561797753, 0.936797752808989, 0.995786516853933, 0.870967741935484, 0.880617977528090, 0.000702247191011236, 0.984550561797753, 0.993679775280899, 0.992977528089888},
            {0.969250480461243, 0.967658473479948, 0.949284785435631, 1, 1, 1, 0.979838709677419, 0.979925650557621, 0.989466292134832, 0, 0.860538827258320, 0.851822503961965},
            {0.982062780269058, 0.979948253557568, 0.959037711313394, 1, 1, 1, 0.989919354838710, 0.987360594795539, 0.995786516853933, 0.865293185419968, 0.000827814569536424, 0.854066985645933},
            {0.975656630365151, 0.971539456662354, 0.949934980494148, 1, 1, 1, 0.986559139784946, 0.984386617100372, 0.991573033707865, 0.858161648177496, 0.854864433811802, 0}
        };

        double[][] distances1 = new double[12][12];

        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                distances1[i][j] = distances[i][j];
            }
        }

        String[] names = new String[]{"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
        ClusteringAlgorithm alg = new DefaultClusteringAlgorithm();
        Cluster cluster = alg.performClustering(distances1, names, new AverageLinkageStrategy());
        cluster.toConsole(0);
        return cluster;
    }

    private static Cluster createSampleClusterFromMatrixJoel(int N, double[][] array, char select) {

        String[] names = new String[N];
        for (int i = 0; i < N; i++) {
            names[i] = String.valueOf(i + 1);
        }

        ClusteringAlgorithm alg = new DefaultClusteringAlgorithm();
        Cluster cluster = null;

        LinkageStrategy l = null;
        switch (select) {

            case 's':
                l = new SingleLinkageStrategy();
                break;

            case 'a':
                l = new AverageLinkageStrategy();
                break;
            case 'c':
                l = new CompleteLinkageStrategy();
                break;

            default:
                l = new AverageLinkageStrategy();

        }

        cluster = alg.performClustering(array, names, l);
        cluster.toConsole(0);
        return cluster;

    }

    /**
     * Joel adds this inner class
     *
     * @author ratsaby
     */
    private static class WindowsOS {

        /**
         * Removes the chars that are not allowed under the Windows OS
         *
         * @param s
         */
        public static String prepareFileName(String s) {

            String temp = new String(s);

            Pattern p = Pattern.compile("[*./:;|=,]");
            Matcher m = p.matcher(temp);
            temp = m.replaceAll("_");

            return temp;

        }

    }
}
