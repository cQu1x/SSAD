import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Asignment3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int boardsize = Integer.parseInt(sc.nextLine());
        Field<Figure> figField = new Field<>(boardsize);
        Field<Coin> coinField = new Field<>(boardsize);
        int[] greenCord = Arrays.stream(sc.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        Green green = new Green(new Position(greenCord[0]-1,greenCord[1]-1));
        green.setColor(Color.GREEN);
        figField.addObject(green,greenCord[0]-1,greenCord[1]-1);
        int[] redCord = Arrays.stream(sc.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        Red red = new Red(new Position(redCord[0]-1,redCord[1]-1));
        red.setColor(Color.RED);
        figField.addObject(red,redCord[0]-1,redCord[1]-1);
        Team greenTeam = new Team(Color.GREEN);
        greenTeam.setObject(0,green);
        Team redTeam = new Team(Color.RED);
        redTeam.setObject(0,red);
        int coinsNumber = Integer.parseInt(sc.nextLine());
        for (int i = 0; i < coinsNumber; i++) {
            int[] coinCord = Arrays.stream(sc.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            coinField.addObject(new Coin(coinCord[2],coinCord[0]-1,coinCord[1]-1),coinCord[0]-1,coinCord[1]-1);
        }
        int nActions = Integer.parseInt(sc.nextLine());
        for (int i = 0; i < nActions; i++) {
            String[] line = sc.nextLine().split(" ");
            switch (line[0]) {
                case "GREEN":
                    if (green.isAlive()){
                        green.processMove(green,line[1],figField,coinField,greenTeam);
                        if (green.makeMove){
                            System.out.println("GREEN MOVED TO "+ (green.getPosition().row+1)+ " "+ (green.getPosition().col+1));
                            green.makeMove = false;
                        }
                    }
                    else{
                        System.out.println("INVALID ACTION");
                    }
                    break;
                case "RED":
                    if (red.isAlive()){
                        red.processMove(red,line[1],figField,coinField,redTeam);
                        if (red.makeMove){
                            System.out.println("RED MOVED TO "+ (red.getPosition().row+1)+ " "+ (red.getPosition().col+1));
                            green.makeMove = false;
                        }
                    }
                    else{
                        System.out.println("INVALID ACTION");
                    }
                    break;
                case "REDCLONE":
                    if (redTeam.getFigure(1)!=null && redTeam.getFigure(1).isAlive()){
                        redTeam.getFigure(1).processMove(redTeam.getFigure(1),line[1],figField,coinField,greenTeam);
                        if (redTeam.getFigure(1).makeMove){
                            System.out.println("REDCLONE MOVED TO "+ (redTeam.getFigure(1).getPosition().row+1)+ " "+ (redTeam.getFigure(1).getPosition().col+1));
                            redTeam.getFigure(1).makeMove = false;
                        }
                    }
                    else{
                        System.out.println("INVALID ACTION");
                    }
                    break;
                case "GREENCLONE":
                    if (greenTeam.getFigure(1)!=null && greenTeam.getFigure(1).isAlive()){
                        greenTeam.getFigure(1).processMove(greenTeam.getFigure(1),line[1],figField,coinField,greenTeam);
                        if (greenTeam.getFigure(1).makeMove){
                            System.out.println("GREENCLONE MOVED TO "+ (greenTeam.getFigure(1).getPosition().row+1)+ " "+ (greenTeam.getFigure(1).getPosition().col+1));
                            greenTeam.getFigure(1).makeMove = false;
                        }
                    }
                    else{
                        System.out.println("INVALID ACTION");
                    }
                    break;
            }
        }
        if (greenTeam.getScore()>redTeam.getScore()){
            System.out.println("GREEN TEAM WINS. SCORE " +greenTeam.getScore() +" "+redTeam.getScore());
        }
        else if (redTeam.getScore()>greenTeam.getScore()){
            System.out.println("RED TEAM WINS. SCORE " +greenTeam.getScore() +" "+redTeam.getScore());
        }
        else{
            System.out.println("TIE. SCORE " + greenTeam.getScore()+ " " + redTeam.getScore());
        }
    }
}
interface TeamComponent {
    int getScore();
}
interface PrototypeFig{
    public abstract Figure cloneFig();
}
interface PlayingStyle{
    public abstract void moveUp(Figure figure, int fieldSize);
    public abstract void moveDown(Figure figure, int fieldSize);
    public abstract void moveLeft(Figure figure, int fieldSize);
    public abstract void moveRight(Figure figure, int fieldSize);
}
class Field<T>{
    private T[][] field;
    private int size;
    Field(int size){
        this.size = size;
        field = (T[][]) new Object[size][size];
    }
    public int getSize(){
        return size;
    }
    public void addObject(T obj, int x, int y){
        field[x][y] = obj;
    }
    public void removeObject(Position position){
        field[position.row][position.col] = null;
    }
    public T[][] getField(){
        return field;
    }
    public T getObject(int x, int y){
        return field[x][y];
    }
    public String defineColor(Figure figure){
        if (figure.getColor()==Color.GREEN && !figure.isClone()){
            return "GREEN";
        }
        else if (figure.getColor()==Color.RED && !figure.isClone()){
            return "RED";
        }
        else if (figure.getColor()==Color.GREEN && figure.isClone()){
            return "GREENCLONE";
        }
        else{
            return "REDCLONE";
        }
    }
    public boolean handleCollision(Figure figure,Position targetPos, Field coinfield){
        if (field[targetPos.row][targetPos.col] != null){
            Figure figure1 = (Figure) field[targetPos.row][targetPos.col];
            if (figure1.getColor()==figure.getColor()){
                System.out.println("INVALID ACTION");
                figure.makeMove = false;
                return false;
            }
            else{
//                System.out.println("Popal suda");
                figure1.die();
                System.out.println(defineColor(figure)+" MOVED TO " + (targetPos.row+1)+" "+(targetPos.col+1) + " AND KILLED " + defineColor(figure1));
                figure.makeMove = false;
                return true;
            }
        }
        else{
            if (coinfield.getField()[targetPos.row][targetPos.col] !=null) {
//                System.out.println("V uslovii");
                Coin coin =(Coin) coinfield.getField()[targetPos.row][targetPos.col];
                figure.increaseScore(coin.getValue());
                coinfield.removeObject(coin.getPosition());
                System.out.println(defineColor(figure)+" MOVED TO " + (targetPos.row+1)+" "+(targetPos.col+1) + " AND COLLECTED " + coin.getValue());
                figure.makeMove = false;
                return true;
            }
        }
        figure.makeMove = true;
//        System.out.println("ТУТОЧКИ");
        return true;
    }
}
class Position{
    public int row;
    public int col;
    Position(int row, int col){
        this.row = row;
        this.col = col;
    }
    void incrementRow(){
        row++;
    }
    void incrementCol(){
        col++;
    }
    @Override
    public boolean equals(Object obj) {
        if(this == obj) {return true;};
        if(!(obj instanceof Position)) {return false;}
        Position other = (Position) obj;
        return this.row == other.row && this.col == other.col;
    }
}
class Coin{
    private int value;
    private Position position;
    public Coin(int value, int x, int y){
        this.value = value;
        this.position = new Position(x, y);
    }
    public int getValue(){
        return value;
    }
    public Position getPosition(){
        return position;
    }
}
class Figure implements PlayingStyle, PrototypeFig, TeamComponent {
    protected int score;
    private Position position;
    protected PlayingStyle playingStyle;
    private Color color;
    private boolean isAlive = true;
    boolean makeMove = false;
    private boolean isClone = false;
    Figure(Position position){
        this.position = position;
        this.score = 0;
        this.playingStyle = new Normal();
    }

    @Override
    public Figure cloneFig(){
        Position reversed = getReversedPosition();
        if (!getPosition().equals(getReversedPosition())){
            Figure clone = new Figure(reversed);
            clone.setColor(this.color);
            clone.makeClone();
            return clone;
        }
        System.out.println("INVALID ACTION");
        return null;
    }
    public boolean isClone(){
        return isClone;
    }
    public void makeClone(){
        this.isClone = true;
    }
    protected Position getPosition(){
        return position;
    }
    public boolean isAlive(){
        return this.isAlive;
    }
    public void die(){
        this.isAlive = false;
    }
    public PlayingStyle getPlayingStyle(){
        return this.playingStyle;
    }
    public void setPosition(Position position){
        this.position = position;
    }
    public void increaseScore(int score){
        this.score += score;
    }
    public Color getColor(){
        return color;
    }
    public void setColor(Color color){
        this.color = color;
    }
    protected Position getReversedPosition() {
        return new Position(position.col, position.row);
    }

    @Override
    public void moveUp(Figure figure, int fieldSize){
        playingStyle.moveUp(figure,fieldSize);
    }
    public  void moveDown(Figure figure, int fieldSize){
        playingStyle.moveDown(figure,fieldSize);
    };
    public void moveLeft(Figure figure,int fieldSize){
        playingStyle.moveLeft(figure,fieldSize);
    };
    public void moveRight(Figure figure, int fieldSize){
        playingStyle.moveRight(figure,fieldSize);
    };

    public void setPlayingStyle(PlayingStyle playingStyle){
        this.playingStyle = playingStyle;
    }

    @Override
    public int getScore() {
        return this.score;
    }
    void processMove(Figure figure, String direction, Field figField, Field coinField, Team team) {
        int offset = (figure.getPlayingStyle() instanceof Attacking) ? 2 : 1;
        Position targetPos = null;
        switch (direction) {
            case "UP":
                targetPos = new Position(figure.getPosition().row - offset, figure.getPosition().col);
                break;
            case "DOWN":
                targetPos = new Position(figure.getPosition().row + offset, figure.getPosition().col);
                break;
            case "LEFT":
                targetPos = new Position(figure.getPosition().row, figure.getPosition().col - offset);
                break;
            case "RIGHT":
                targetPos = new Position(figure.getPosition().row, figure.getPosition().col + offset);
                break;
            case "STYLE":
                if (figure.getPlayingStyle() instanceof Normal) {
                    figure.setPlayingStyle(new Attacking());
                    System.out.println(figField.defineColor(figure)+ " CHANGED STYLE TO ATTACKING");
                } else {
                    figure.setPlayingStyle(new Normal());
                    System.out.println(figField.defineColor(figure) + " CHANGED STYLE TO NORMAL");
                }
                figure.makeMove=false;
                return;
            case "COPY":
                if (figure.isAlive() && team.getFigure(1) == null) {
                    Figure clone = figure.cloneFig();
                    if (clone == null) {
                        System.out.println("INVALID ACTION");}
                    else if (coinField.getField()[clone.getPosition().row][clone.getPosition().col]!=null) {
                        System.out.println("INVALID ACTION");
                        } else {
                        team.setObject(1, clone);
                        figField.addObject(clone, clone.getPosition().row, clone.getPosition().col);
                        System.out.println(figure.getColor().toString().toUpperCase() + " CLONED TO " +
                                (clone.getPosition().row + 1) + " " + (clone.getPosition().col + 1));
                    }
                } else {
                    System.out.println("INVALID ACTION");
                }
                figure.makeMove=false;
                return;
        }

        if (targetPos.row < 0 || targetPos.row >= figField.getSize() ||
                targetPos.col < 0 || targetPos.col >= figField.getSize()) {
            System.out.println("INVALID ACTION");
            figure.makeMove = false;
            return;
        }

        if (figField.handleCollision(figure, targetPos, coinField)) {
            figField.removeObject(figure.getPosition());
            switch(direction) {
                case "UP": figure.moveUp(figure, figField.getSize()); break;
                case "DOWN": figure.moveDown(figure, figField.getSize()); break;
                case "LEFT": figure.moveLeft(figure, figField.getSize()); break;
                case "RIGHT": figure.moveRight(figure, figField.getSize()); break;
            }
            figField.addObject(figure, figure.getPosition().row, figure.getPosition().col);
        }
    }

}
enum Color{
    GREEN,
    RED,
}

class Team implements TeamComponent {
    private ArrayList<TeamComponent> team;
    private Color teamColor;
    Team(Color teamColor){
        this.team = new ArrayList<>(2);
        this.team.add(0,null);
        this.team.add(1,null);
        this.teamColor = teamColor;
    }
    public void addMember(TeamComponent teamComponent){
        team.add(teamComponent);
    }
    public void setObject(int index, TeamComponent teamComponent) {
        team.set(index, teamComponent);
    }
    public void removeMember(TeamComponent teamComponent){
        team.remove(teamComponent);
    }
    @Override
    public int getScore() {
        int totalScore = 0;
        for (TeamComponent teamComponent : team) {
            if(teamComponent != null){
                totalScore += teamComponent.getScore();
            }
        }
        return totalScore;
    }
    public Color getTeamColor(){
        return teamColor;
    }
    public Figure getFigure(int index){
        return (Figure) team.get(index);
    }
}
class Green extends Figure {
    Green(Position position) {
        super(position);
    }

    @Override
    public Figure cloneFig(){
        Position reversed = getReversedPosition();
        if (!getPosition().equals(reversed)){
            GreenCopy clone = new GreenCopy(reversed);
            clone.setColor(this.getColor());
            clone.makeClone();
            return clone;
        }
        return null;
    }
}

class GreenCopy extends Green {
    GreenCopy(Position position) {
        super(position);
    }

    @Override
    public Figure cloneFig(){
        return null;
    }
}

class Red extends Figure {
    Red(Position position) {
        super(position);
    }
    @Override
    public Figure cloneFig(){
        Position reversed = getReversedPosition();
        if (!getPosition().equals(reversed)){
            GreenCopy clone = new GreenCopy(reversed);
            clone.setColor(this.getColor());
            clone.makeClone();
            return clone;
        }
        return null;
    }
}

class RedCopy extends Red {
    RedCopy(Position position) {
        super(position);
    }

    @Override
    public Figure cloneFig(){
        return null;
    }
}

class Normal implements PlayingStyle{
    @Override
    public void moveUp(Figure figure, int fieldSize){
        if (figure.getPosition().row-1>=0){
            figure.setPosition(new Position(figure.getPosition().row-1,figure.getPosition().col));
        }
        else{
            System.out.println("INVALID ACTION");
        }
    }
    @Override
    public void moveDown(Figure figure, int fieldSize){
        if (figure.getPosition().row+1<=fieldSize){
            figure.setPosition(new Position(figure.getPosition().row+1,figure.getPosition().col));
        }
        else{
            System.out.println("INVALID ACTION");
        }
    }    @Override
    public void moveLeft(Figure figure, int fieldSize){
        if (figure.getPosition().col-1>=0){
            figure.setPosition(new Position(figure.getPosition().row,figure.getPosition().col-1));
        }
        else{
            System.out.println("INVALID ACTION");
        }
    }    @Override
    public void moveRight(Figure figure, int fieldSize){
        if (figure.getPosition().col+1<=fieldSize){
            figure.setPosition(new Position(figure.getPosition().row,figure.getPosition().col+1));
        }
        else{
            System.out.println("INVALID ACTION");
        }
    }
}

class Attacking implements PlayingStyle{
    @Override
    public void moveUp(Figure figure, int fieldSize){
        if (figure.getPosition().row-2>=0){
            figure.setPosition(new Position(figure.getPosition().row-2,figure.getPosition().col));
        }
        else{
            System.out.println("INVALID ACTION");
        }
    }
    @Override
    public void moveDown(Figure figure, int fieldSize){
        if (figure.getPosition().row+2<=fieldSize){
            figure.setPosition(new Position(figure.getPosition().row+2,figure.getPosition().col));
        }
        else{
            System.out.println("INVALID ACTION");
        }
    }    @Override
    public void moveLeft(Figure figure, int fieldSize){
        if (figure.getPosition().col-2>=0){
            figure.setPosition(new Position(figure.getPosition().row,figure.getPosition().col-2));
        }
        else{
            System.out.println("INVALID ACTION");
        }
    }    @Override
    public void moveRight(Figure figure, int fieldSize){
        if (figure.getPosition().col+2<=fieldSize){
            figure.setPosition(new Position(figure.getPosition().row,figure.getPosition().col+2));
        }
        else{
            System.out.println("INVALID ACTION");
        }
    }
}