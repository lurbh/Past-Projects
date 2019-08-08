<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/forecast">
<html>
<head>
  <title>Assignment 7 Solution</title>
</head>
<style>
  .day{
    color: blue; 
  }

  .overall{
    font-style: italic;
  }

  .hightemp{
    font-size: 25px;
  }

  .lowtemp{
    font-size: 15px;
  }
</style>
<body>
  <h1><b>Assignment 7 Solutuion</b></h1>
  <hr />
  <b>I have read the policy for plagiarism at Wollongong University.</b> <br />
  <b>I declare that this assignment solution is enirely my work.</b> <br />
  <hr />

  <h1><b>Part 1</b></h1>
  <table border="2" width="50%">
    <tr>
      <td colspan="2"><b>STUDENT DETAILS</b></td>
    </tr>
    <tr>
      <td width="30%">STUDENT NUMBER</td>
        <td>6212748</td>
    </tr>
    <tr>
      <td width="30%">STUDENT FAMILY NAME</td>
        <td>LUR</td>
    </tr>
    <tr>
      <td width="30%">STUDENT GIVEN NAME</td>
        <td>BING HUII</td>
    </tr>
    <tr>
      <td width="30%">UOW EMAIL</td>
        <td>bhl736@uowmail.edu.au</td>
    </tr>
    <tr>
      <td colspan="2"><b>ASSIGNMENT DETAILS</b></td>
    </tr>
    <tr>
      <td width="30%">SUBJECT CODE</td>
        <td>CSIT128</td>
    </tr>
    <tr>
      <td width="30%">SUBJECT NAME</td>
        <td>Introduction to Web Technology</td>
    </tr>
    <tr>
      <td width="30%">ASSIGNMENT NUMBER</td>
        <td>7</td>
    </tr>
    <tr>
      <td width="30%">ASSIGNMENT DUE DATE</td>
        <td>19/02/2019</td>
    </tr>
    <tr>
      <td width="30%">LAB TIME</td>
        <td>12:00</td>
    </tr>
  </table>
  <hr />
  <h1><b>Part 2</b></h1>
  <h4><b><xsl:value-of select="@queryLocation" /> @ <xsl:value-of select="@queryTime" /></b></h4>
  <table border="0">
  <xsl:for-each select="weather">
    <tr>
      <td align="center" width="150">
        <font class="day"><xsl:value-of select="dayOfWeek"/></font>&#160;<xsl:value-of select="month"/>/<xsl:value-of select="date"/>
        <br />
        <img>
          <xsl:attribute name="src">
            <xsl:value-of select="overallCode"/><xsl:text>.png</xsl:text>
          </xsl:attribute>
          <xsl:attribute name="width">
            <xsl:text>50px</xsl:text>
          </xsl:attribute>
        </img>
      </td>
      <td width="200">
        <font class="overall"><xsl:value-of select="overall"/></font>
        <br />
        <font class="hightemp"><xsl:value-of select="highest"/>&#176;</font>/<font class="lowtemp"><xsl:value-of select="lowest"/>&#176;</font>
      </td>
    </tr>
  </xsl:for-each>
  </table>
  <hr />
  <h1><b>Part 3</b></h1>
  <h4><b><xsl:value-of select="@queryLocation" /> @ <xsl:value-of select="@queryTime" /></b></h4>
  <table border="0" style="table-layout: fixed;" width="750px">
    <tr>
      <xsl:for-each select="weather">
        <td width="150px" align="center">
          <font class="day"><xsl:value-of select="dayOfWeek"/></font>&#160;<xsl:value-of select="month"/>/<xsl:value-of select="date"/>
        </td>
      </xsl:for-each>
    </tr>
    <tr>
      <xsl:for-each select="weather">
        <td align="center">
          <img>
          <xsl:attribute name="src">
            <xsl:value-of select="overallCode"/><xsl:text>.png</xsl:text>
          </xsl:attribute>
          <xsl:attribute name="width">
            <xsl:text>50px</xsl:text>
          </xsl:attribute>
        </img>
        </td>
      </xsl:for-each>
    </tr>
    <tr>
      <xsl:for-each select="weather">
        <td align="center">
          <font class="hightemp"><xsl:value-of select="highest"/>&#176;</font>/<font class="lowtemp"><xsl:value-of select="lowest"/>&#176;</font>
        </td>
      </xsl:for-each>
    </tr>
    <tr>
      <xsl:for-each select="weather">
        <td align="center">
          <font class="overall"><xsl:value-of select="overall"/></font>
        </td>
      </xsl:for-each>
    </tr>
  </table>
  <hr />
  <text>© Lur Bing Huii</text>
</body>
</html>
</xsl:template>
</xsl:stylesheet>
