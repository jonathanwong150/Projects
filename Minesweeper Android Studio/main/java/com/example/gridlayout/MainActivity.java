package com.example.gridlayout;

import androidx.appcompat.app.AppCompatActivity;
import androidx.gridlayout.widget.GridLayout;

import android.content.Intent;
import android.content.res.Resources;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.TextView;

import org.w3c.dom.Text;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private static final int COLUMN_COUNT = 8;
    private ArrayList<TextView> cells;
    // Create x and y ArrayLists to check adjacent squares easily
    private ArrayList<Integer> x = new ArrayList<Integer>();
    private ArrayList<Integer> y = new ArrayList<Integer>();
    // ArrayList with all cell values in order 0-79
    private ArrayList<String> all = new ArrayList<String>();
    // Create ArrayList to track which cells have been visited
    private ArrayList<Boolean> visited = new ArrayList<>();

    // Private variable to check if in mine or flag mode
    private boolean pick=true;
    private boolean running=true;
    // Variables that contain flags remaining, revealed squares, and seconds passed
    private int flags_left=4;
    private int revealed=0;
    private int seconds=0;

    private int dpToPixel(int dp) {
        float density = Resources.getSystem().getDisplayMetrics().density;
        return Math.round(dp * density);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize private variable
        cells = new ArrayList<TextView>();

        // Start the timer and generate 4 random mines
        startTimer();
        dropMines();

        // Dynamically create a 10x8 grid with correct values
        GridLayout grid = (GridLayout) findViewById(R.id.gridLayout01);
        for (int i = 0; i<10; i++) {
            for (int j=0; j<8; j++) {
                TextView tv = new TextView(this);
                tv.setHeight(dpToPixel(40));
                tv.setWidth(dpToPixel(40));
                tv.setTextSize(32);
                // Align and set colors
                tv.setTextAlignment(TextView.TEXT_ALIGNMENT_CENTER);
                tv.setTextColor(Color.GRAY);
                tv.setBackgroundColor(Color.GREEN);
                // Check mines in adjacent squares
                int mine_count=0;
                // Keep track if square IS a mine
                boolean is_mine=false;
                // Loop through each of the mines
                for(int mine=0;mine<4;mine++) {
                    // Find the x and y coordinates of each mine
                    int xMine= x.get(mine);
                    int yMine=y.get(mine);
                    // Check if current square is mine, if it is set boolean and continue
                    if(i==xMine && j==yMine){
                        is_mine = true;
                    } else if((j >= yMine - 1 && j <= yMine + 1) && (i >= xMine - 1 && i <= xMine + 1)) {
                        mine_count += 1;
                    }
                }
                // Set the value of cell to the number of mines adjacent
                tv.setText(String.valueOf(mine_count));
                // Add  the value to ArrayList with all cells
                if(!is_mine){
                    all.add(String.valueOf(mine_count));
                }else{
                    all.add(getString(R.string.mine));
                }
                // Set text color to hide number and append to visited
                tv.setTextColor(Color.GREEN);
                visited.add(false);

                GridLayout.LayoutParams lp = new GridLayout.LayoutParams();
                lp.setMargins(dpToPixel(2), dpToPixel(2), dpToPixel(2), dpToPixel(2));
                lp.rowSpec = GridLayout.spec(i);
                lp.columnSpec = GridLayout.spec(j);

                grid.addView(tv, lp);
                tv.setOnClickListener(this::onClickTV);
                cells.add(tv);
            }
        }
    }

    private int findIndexOfCellTextView(TextView tv) {
        for (int n=0; n<cells.size(); n++) {
            if (cells.get(n) == tv)
                return n;
        }
        return -1;
    }

    public void dropMines(){
        // Drops 4 mines
        int mines_left=4;
        Random rand = new Random();
        while(mines_left>0){
            // Generate a random x and y coordinated with correct bounds
            int xMine = rand.nextInt(10);
            int yMine = rand.nextInt(8);
            // Continue to generate new mines until values are unique
            boolean new_value=false;
            while (!new_value) {
                boolean exists = false;
                // Loop through existing mines
                for (int i = 0; i < x.size(); i++) {
                    // If mine has EXACT coordinates as existing mine
                    if (xMine == x.get(i) && yMine == y.get(i)) {
                        // Generate new mine and mark as an existing mine
                        xMine = rand.nextInt(10);
                        yMine = rand.nextInt(8);
                        exists=true;
                    }
                }
                // If mine does not exist, break loop and add to x and y ArrayLists
                if(!exists){
                    new_value = true;
                }
            }
            x.add(xMine);
            y.add(yMine);
            mines_left--;
        }
    }
    public void onClickTV(View view){
        // Generate textview and flag objects
        TextView tv = (TextView) view;
        TextView flag = findViewById(R.id.flags_left);
        // Find index, row, and column
        int n = findIndexOfCellTextView(tv);
        int row=n/COLUMN_COUNT;
        int col=n%COLUMN_COUNT;
        // Check if we are mining a non-flagged square
        if(pick && tv.getText() != getString(R.string.flag)){
            // If the square has a mine
            if(all.get(n) == getString(R.string.mine)){
                // Reveal the mine and pass loss into endGame function
                tv.setText(R.string.mine);
                tv.setBackgroundColor(Color.RED);
                endGame(false);
            // If we mine a 0, reveal all surrounding 0s by passing row and col
            }else if(all.get(n).equals("0")) {
                reveal(row,col);
            // If mining a normal square, reveal
            }else{
                tv.setText(all.get(n));
                tv.setTextColor(Color.GRAY);
                tv.setBackgroundColor(Color.LTGRAY);
                visited.set(n,true);
                revealed++;
            }
        // Flag mode
        }else if(!pick){
            // Unflagging an item
            if(tv.getText()==getString(R.string.flag)){
                // Set to correct number value and increment flags remaining
                tv.setText("");
                flags_left++;
                flag.setText(String.valueOf(flags_left));
            // Flag square if we have remaining flags
            }else if(tv.getCurrentTextColor()==Color.GREEN){
                // Set text to  flag and decrement flags remaining
                tv.setText(getString(R.string.flag));
                flags_left--;
                flag.setText(String.valueOf(flags_left));
            }
        }
        // After each click, check win condition
        if(revealed==76){
            endGame(true);
        }
    }

    // Function to change between click and flag
    public void pickClicked(View view){
        if(pick){
            pick=false;
        }else{
            pick=true;
        }
    }

    // Function that starts timer
    public void startTimer(){
        // Create timer object
        TextView timer = findViewById(R.id.time_elapsed);
        Handler handler = new Handler();
        handler.post(new Runnable() {
            @Override
            public void run(){
                // Increment seconds passed while game is active
                if(running){
                    seconds++;
                }
                // Set timer value
                timer.setText(String.valueOf(seconds));
                // Call method with delay to update clock
                handler.postDelayed(this, 1000);
            }
        });
    }

    // Method to reveal all adjacent 0s
    public void reveal(int row, int col){
        // Utilize LinkedList to implement a Queue
        Queue<Integer> xQ = new LinkedList<>();
        Queue<Integer> yQ = new LinkedList<>();
        // Add current row and column to each Queue
        xQ.add(row);
        yQ.add(col);
        // Continue loop as long as queue is not empty
        while (xQ.size() > 0) {
            // Grab current x and y coordinates
            int x = xQ.remove();
            int y = yQ.remove();
            // Check which cell we currently have
            int n = x * 8 + y;
            // Check if we have already visited node and set node as visited
            if(!visited.get(n)) {
                visited.set(n, true);
            }else{
                continue;
            }
            // Create variables for tv object and current value
            TextView tv = cells.get(n);
            String num = all.get(n);
            // Reveal the squares
            tv.setTextColor(Color.GRAY);
            tv.setBackgroundColor(Color.LTGRAY);
            revealed+=1;
            // Add to queue if surrounding values are equal to 0
            if(num.equals("0")) {
                // Check the square above
                if(x - 1 >=0) {
                    xQ.add(x - 1);
                    yQ.add(y);
                }
                // Check square to left
                if(y - 1 >= 0) {
                    xQ.add(x);
                    yQ.add(y - 1);
                }
                // Check square below
                if(x + 1 < 10) {
                    xQ.add(x + 1);
                    yQ.add(y);
                }
                // Check square to right
                if(y + 1 < 8) {
                    xQ.add(x);
                    yQ.add(y + 1);
                }
                // Check top left square
                if(x - 1 >= 0 && y - 1 >= 0) {
                    xQ.add(x - 1);
                    yQ.add(y - 1);
                }
                // Check bottom left square
                if(x + 1 < 10 && y - 1 >= 0) {
                    xQ.add(x + 1);
                    yQ.add(y - 1);
                }
                // Check top right square
                if(x - 1 >= 0 && y + 1 < 8) {
                    xQ.add(x - 1);
                    yQ.add(y + 1);
                }
                // Check bottom right square
                if(x + 1 < 10 && y + 1 < 8) {
                    xQ.add(x + 1);
                    yQ.add(y + 1);
                }
            }
        }
        if(revealed==76){
            endGame(true);
        }
    }
    public void endGame(Boolean win){
        // Stop time
        running=false;
        // Transition to second screen if win
        // Created new activity and intent
        Intent intent = new Intent(MainActivity.this, GameOver.class);
        // Pass seconds to the next screen
        intent.putExtra("time", String.valueOf(seconds));
        // Pass resulting win or loss depending on boolean
        if(win){
            // Reveal remaining mines in green
            for (int i=0;i<x.size();i++){
                // Get mine coordinates
                int xMine=x.get(i);
                int yMine=y.get(i);
                int n= xMine * 8 +yMine;
                // Find each cell and set cells to mines
                TextView tv = cells.get(n);
                tv.setText(getString(R.string.mine));
                //tv.setBackgroundColor(Color.GREEN);
            }
            intent.putExtra("result", "lost");
            intent.putExtra("result", "won");
        }else{
            // Reveal all mines if lose in red
            for (int i=0;i<x.size();i++){
                // Get mine coordinates
                int xMine=x.get(i);
                int yMine=y.get(i);
                int n= xMine * 8 +yMine;
                // Find each cell and set cells to mines
                TextView tv = cells.get(n);
                tv.setText(getString(R.string.mine));
                tv.setBackgroundColor(Color.RED);
            }
            intent.putExtra("result", "lost");
        }
        // Start new activity
        startActivity(intent);
    }
}