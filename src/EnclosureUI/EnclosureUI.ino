/* UI for audio project displaying voltage, amperage, temperature, and humidity of enclosed enviorment(3/4" plywood) */

#include <memorysaver.h>
#include <UTFT.h>

/* Designitated initializer for UTFT: (chipset,RS,WR,CS,RST) */
UTFT lcd(TFT01_43,38,39,40,41);

extern uint8_t SmallFont[];
extern uint8_t BigFont[];

void setup() {
  
  lcd.clrScr();
  lcd.InitLCD(LANDSCAPE);
  lcd.setFont(BigFont);
  lcd.setContrast(30);
  lcd.fillScr(VGA_BLACK);
  lcd.setColor(VGA_GREEN);
  drawSensorGrid();
}

int getFontWidth() {

    return lcd.getFontXsize();
}

int getFontHeight() {

    return lcd.getFontYsize();
}

int getMaxWidth() {

  return lcd.getDisplayXSize(); //480
}

int getMaxHeight() {

  return lcd.getDisplayYSize(); //272
}

int getHeaderHeight() {

    return 45;
}

int getBorderWidth() {

  return 10;
}

int getHeaderYInset() {

  return 60;
}

int getStrLengthInPixels(char *str) {

  return ((getFontWidth() * strlen(str))/2);
}

void drawSensorGrid() {
  
  drawContainer();
  drawColumnsWithContext();
}

void drawColumnsWithContext() {

 //TODO: Pass this in as a param
 char* columnTitles[] = {"Volts", "Amps", "Temp", "Humidity"};
 int columnTitlesLength = sizeof(columnTitles) / sizeof(char *);
 int columnWidth = getMaxWidth()/columnTitlesLength;
 int yPos = getHeaderYInset() + getBorderWidth();
 int titleYInset = 20;

 /* Draw Columns */
  for (int i = 0; i < columnTitlesLength; i++) {
    lcd.fillRect(columnWidth * i, yPos, columnWidth * i + getBorderWidth(), getMaxHeight());
    
    int strLengthInPixels = getStrLengthInPixels(columnTitles[i]);
    int columnCenter = columnWidth/2;
    int columnXStart = columnWidth * i;
    int borderCenter = getBorderWidth()/2;

    /* Calculate column width for context X coordinate */
    int xPos = columnXStart + columnCenter + borderCenter - getStrLengthInPixels(columnTitles[i]);
    lcd.print(columnTitles[i], xPos, yPos + titleYInset);
  }
}

void drawContainer() {

  /* Set container style */
  lcd.setColor(VGA_RED);
  lcd.setFont(SmallFont); // <-- Pick a bigger font!

  /* Draw header */
  lcd.fillRect(0, getHeaderYInset(), getMaxWidth() - 1, getHeaderYInset() + getBorderWidth());

  /* Draw top edge */
  lcd.fillRect(0, 0 , getMaxWidth() -1, getBorderWidth());
  
  /* Draw bottom edge */
  lcd.fillRect(0, getMaxHeight() - getBorderWidth(), getMaxWidth() - 1, getMaxHeight());

  /* Draw left edge */
  lcd.fillRect(0, 0, getBorderWidth(), getMaxHeight());

  /* Draw right edge */
  lcd.fillRect(getMaxWidth() - 1, 0, getMaxWidth() - getBorderWidth() , getMaxHeight());
}

void loop() {}
