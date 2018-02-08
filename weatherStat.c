function checkUpdates() //checks that all the sensors are sending data
{
  var two_hours = 2*1000*60*60;
  //temperature
  var ss = SpreadsheetApp.openById('0AsC_5HAGXRaudG1CUlJUWGtBUHpESmRHeFVPbWxIMnc');
  var sh = ss.getSheets()[0];
  var row = sh.getLastRow();
  var tempDate = sh.getRange(row, 1,1,1).getValue();
  var tempUpdate = tempDate.getTime();
  
  //wind direction
  ss = SpreadsheetApp.openById('0AsC_5HAGXRaudDFnOEpPSUhLcmNYMi1CM0Y4SDJfZnc');
  sh = ss.getSheets()[0];
  row = sh.getLastRow();
  var windDate = sh.getRange(row, 1,1,1).getValue();
  var windUpdate = windDate.getTime();
  
  //total rain
  ss = SpreadsheetApp.openById('0AsC_5HAGXRaudE9JTnBISTFKclhodXdfZGh1bDBlWHc');
  sh = ss.getSheets()[0];
  row = sh.getLastRow();
  var rainDate = sh.getRange(row, 1,1,1).getValue();
  var rainUpdate = rainDate.getTime();
  
  var current = new Date().getTime();
  
  if(current-rainUpdate>two_hours || current-windUpdate>two_hours || current-tempUpdate>two_hours)
    MailApp.sendEmail("y.shifman@gmail.com", " תחנת מזג אוויר: סנסורים לא משדרים", "עדכון גשם אחרון: " + rainDate + "\n" + " עדכון טמפרטורה אחרון: " + tempDate +"\n" + " עדכון רוח אחרון: " + windDate+"\n");
  
} 


function getLatest() //writes latest data to ss
{   
  //humidity
  var ss = SpreadsheetApp.openById('0AsC_5HAGXRaudG13bEtNdV9KNGx4WW1udjdLZWpMTWc');
  var sh = ss.getSheets()[0];// access first sheet (0 indexed)
  var row = sh.getLastRow();
  var hum = sh.getRange(row, 1,1,2).getValues()
  
  //wind direction
  ss = SpreadsheetApp.openById('0AsC_5HAGXRaudDFnOEpPSUhLcmNYMi1CM0Y4SDJfZnc');
  sh = ss.getSheets()[0];
  row = sh.getLastRow();
  var dir = sh.getRange(row, 1,1,2).getValues();
  
  //wind current speed
  ss = SpreadsheetApp.openById('0AsC_5HAGXRaudEFvRS1qTWo3RDJnTkpGMVJPMkxYTHc');
  sh = ss.getSheets()[0];
  row = sh.getLastRow();
  var cur = sh.getRange(row, 1,1,2).getValues();
  
  //wind average speed
  ss = SpreadsheetApp.openById('0AsC_5HAGXRaudGtzb0ptOFc5RzNybUstMUJHcDB1RXc');
  sh = ss.getSheets()[0];
  row = sh.getLastRow();
  var avg = sh.getRange(row, 1,1,2).getValues();
  
  //total rain
  ss = SpreadsheetApp.openById('0AsC_5HAGXRaudE9JTnBISTFKclhodXdfZGh1bDBlWHc');
  sh = ss.getSheets()[0];
  row = sh.getLastRow();
  var tot = sh.getRange(row, 1,1,2).getValues();
  
  //rain rate
  ss = SpreadsheetApp.openById('0AsC_5HAGXRaudElnRjhHNzd3TzdZdnA4bjRBUWt4bVE');
  sh = ss.getSheets()[0];
  row = sh.getLastRow();
  var rate = sh.getRange(row, 1,1,2).getValues();
  
  
  //temperature
  ss = SpreadsheetApp.openById('0AsC_5HAGXRaudG1CUlJUWGtBUHpESmRHeFVPbWxIMnc');
  sh = ss.getSheets()[0];
  row = sh.getLastRow();
  var temp = sh.getRange(row, 1,1,2).getValues();
  
  temp[0][1] 
  hum[0][1] += "%";
  dir[0][1] += "º";
  avg[0][1] += " קמ\"ש";
  cur[0][1] += " קמ\"ש";
  tot[0][1] += " מ\"מ";
  rate[0][1] += " מ\"מ לשעה";
  
  //write data
  sh.getRange(3,4,1,2).setValues(temp);
  sh.getRange(4,4,1,2).setValues(hum);
  sh.getRange(5,4,1,2).setValues(dir);
  sh.getRange(6,4,1,2).setValues(avg);
  sh.getRange(7,4,1,2).setValues(cur);
  sh.getRange(8,4,1,2).setValues(tot);
  sh.getRange(9,4,1,2).setValues(rate);
}




function getMaxMin()//writes min/max data to ss
{
  //humidity
  var ss = SpreadsheetApp.openById('0AsC_5HAGXRaudG13bEtNdV9KNGx4WW1udjdLZWpMTWc');
  var sh = ss.getSheets()[0];
  var values = sh.getRange("A:B").getValues();
  var maxH=0;
  var minH=100;
  var minHDate=0;
  var maxHDate=0;
  for(var k=0;k< values.length;k++){
    if(values[k][0]!=0){
      if(values[k][1]>=maxH){
        maxH=values[k][1];
        maxHDate=values[k][0];
      }
    
      if(values[k][1]<=minH){
        minH=values[k][1];
        minHDate=values[k][0];
      }
    }
  }

  
  //current wind speed
  ss = SpreadsheetApp.openById('0AsC_5HAGXRaudEFvRS1qTWo3RDJnTkpGMVJPMkxYTHc');
  sh = ss.getSheets()[0];
  values = sh.getRange("A:B").getValues();
  var maxW=0;
  var maxWDate=0;
  for(var k=0;k< values.length;k++){
    if(values[k][1]>=maxW){
      maxW=values[k][1];
      maxWDate=values[k][0];
    }
  }
  
  //rain rate
  ss = SpreadsheetApp.openById('0AsC_5HAGXRaudElnRjhHNzd3TzdZdnA4bjRBUWt4bVE');
  sh = ss.getSheets()[0];
  values = sh.getRange("A:B").getValues();
  var maxR=-1;
  var maxRDate=0;
  for(var k=0;k< values.length;k++){
    if(values[k][0]!=0){
      if(values[k][1]>=maxR){
        maxR=values[k][1];
        maxRDate=values[k][0];
      }
    }
  }
  
  //temperature
  ss = SpreadsheetApp.openById('0AsC_5HAGXRaudG1CUlJUWGtBUHpESmRHeFVPbWxIMnc');
  sh = ss.getSheets()[0];
  values = sh.getRange("A:B").getValues();
  var maxT=0;
  var minT=100;
  var minTDate=0;
  var maxTDate=0;
  for(var k=0;k< values.length;k++){
    if(values[k][0]!=0){
      if(values[k][1]>=maxT){
        maxT=values[k][1];
        maxTDate=values[k][0];
      }
      if(values[k][1]<=minT){
        minT=values[k][1];
        minTDate=values[k][0];
      }
    }
  }
  
  maxH += "%";
  minH += "%";
  maxT += "ºC";
  minT += "ºC";
  maxW += " קמ\"ש";
  maxR += " מ\"מ לשעה";
  
  sh.getRange(11,4,1,1).setValue(maxTDate);
  sh.getRange(11,5,1,1).setValue(maxT);
  sh.getRange(12,4,1,1).setValue(minTDate);
  sh.getRange(12,5,1,1).setValue(minT);
  sh.getRange(13,4,1,1).setValue(maxHDate);
  sh.getRange(13,5,1,1).setValue(maxH);
  sh.getRange(14,4,1,1).setValue(minHDate);
  sh.getRange(14,5,1,1).setValue(minH);
  sh.getRange(15,4,1,1).setValue(maxWDate);
  sh.getRange(15,5,1,1).setValue(maxW);
  sh.getRange(16,4,1,1).setValue(maxRDate);
  sh.getRange(16,5,1,1).setValue(maxR);
  
  var date=new Date();
  sh.getRange(17,4,1,1).setValue(date);
  
  //var diff  = date.getTime()-maxRDate.getTime(); time difference in ms

  
}
  
