/* 
**  Font data for Times New Roman 14pt
*/

/* Character bitmaps for Times New Roman 14pt */
const unsigned char timesNewRoman_14ptBitmaps[] = 
{
	/* @0 '0' (8 pixels wide) */
	0x3C, //   ####  
	0x66, //  ##  ## 
	0x42, //  #    # 
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0x42, //  #    # 
	0x66, //  ##  ## 
	0x3C, //   ####  

	/* @12 '1' (6 pixels wide) */
	0x30, //   ##  
	0xF0, // ####  
	0x30, //   ##  
	0x30, //   ##  
	0x30, //   ##  
	0x30, //   ##  
	0x30, //   ##  
	0x30, //   ##  
	0x30, //   ##  
	0x30, //   ##  
	0x30, //   ##  
	0xFC, // ######

	/* @24 '2' (8 pixels wide) */
	0x3C, //   ####  
	0x4E, //  #  ### 
	0x86, // #    ## 
	0x06, //      ## 
	0x06, //      ## 
	0x04, //      #  
	0x08, //     #   
	0x18, //    ##   
	0x10, //    #    
	0x21, //   #    #
	0x7F, //  #######
	0xFE, // ####### 

	/* @36 '3' (8 pixels wide) */
	0x3C, //   ####  
	0xCE, // ##  ### 
	0x86, // #    ## 
	0x06, //      ## 
	0x0C, //     ##  
	0x1E, //    #### 
	0x07, //      ###
	0x03, //       ##
	0x03, //       ##
	0x03, //       ##
	0xC6, // ##   ## 
	0xF8, // #####   

	/* @48 '4' (8 pixels wide) */
	0x06, //      ## 
	0x06, //      ## 
	0x0E, //     ### 
	0x16, //    # ## 
	0x26, //   #  ## 
	0x26, //   #  ## 
	0x46, //  #   ## 
	0x86, // #    ## 
	0xFF, // ########
	0x06, //      ## 
	0x06, //      ## 
	0x06, //      ## 

	/* @60 '5' (7 pixels wide) */
	0x1E, //    ####
	0x3E, //   #####
	0x20, //   #    
	0x30, //   ##   
	0x7C, //  ##### 
	0x0E, //     ###
	0x06, //      ##
	0x02, //       #
	0x02, //       #
	0x02, //       #
	0xC4, // ##   # 
	0xF8, // #####  

	/* @72 '6' (8 pixels wide) */
	0x07, //      ###
	0x1C, //    ###  
	0x30, //   ##    
	0x60, //  ##     
	0x5C, //  # ###  
	0xE6, // ###  ## 
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0x66, //  ##  ## 
	0x3C, //   ####  

	/* @84 '7' (8 pixels wide) */
	0x7F, //  #######
	0x7E, //  ###### 
	0x82, // #     # 
	0x04, //      #  
	0x04, //      #  
	0x04, //      #  
	0x08, //     #   
	0x08, //     #   
	0x10, //    #    
	0x10, //    #    
	0x10, //    #    
	0x20, //   #     

	/* @96 '8' (7 pixels wide) */
	0x7C, //  ##### 
	0xC6, // ##   ##
	0xC6, // ##   ##
	0xC4, // ##   # 
	0x68, //  ## #  
	0x38, //   ###  
	0x6C, //  ## ## 
	0xC6, // ##   ##
	0xC6, // ##   ##
	0xC6, // ##   ##
	0xE6, // ###  ##
	0x78, //  ####  

	/* @108 '9' (8 pixels wide) */
	0x3C, //   ####  
	0x66, //  ##  ## 
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0xC3, // ##    ##
	0x63, //  ##   ##
	0x3E, //   ##### 
	0x06, //      ## 
	0x0C, //     ##  
	0x18, //    ##   
	0xE0, // ###     
};

/* Character descriptors for Times New Roman 14pt */
/* { [Char width in bits], [Offset into timesNewRoman_14ptCharBitmaps in bytes] } */
const FONT_CHAR_INFO timesNewRoman_14ptDescriptors[] = 
{
	{8, 0}, 		/* 0 */ 
	{6, 12}, 		/* 1 */ 
	{8, 24}, 		/* 2 */ 
	{8, 36}, 		/* 3 */ 
	{8, 48}, 		/* 4 */ 
	{7, 60}, 		/* 5 */ 
	{8, 72}, 		/* 6 */ 
	{8, 84}, 		/* 7 */ 
	{7, 96}, 		/* 8 */ 
	{8, 108}, 		/* 9 */ 
};

/* Font information for Times New Roman 14pt */
const FONT_INFO timesNewRoman_14ptFontInfo =
{
	2, /*  Character height */
	'0', /*  Start character */
	'9', /*  End character */
	2, /*  Width, in pixels, of space character */
	timesNewRoman_14ptDescriptors, /*  Character descriptor array */
	timesNewRoman_14ptBitmaps, /*  Character bitmap array */
};

