//
//  IOSContext.h
//  AirGraghics
//
//  Created by  on 12-9-4.
//  Copyright (c) 2012年 hao peng. All rights reserved.
//

#ifndef AirGraghics_IOSContext_h
#define AirGraghics_IOSContext_h
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>
#include "AirGraphicsUtility.h"
char*  OSLoadPNG ( const char *fileName, int *width, int *height )
{
	NSString *filePath = [NSString stringWithUTF8String: fileName];
    UIImage *image = [UIImage imageNamed:filePath];
    if (image == nil) {
        NSData *texData = [[NSData alloc] initWithContentsOfFile:filePath];

        image = [[UIImage alloc] initWithData:texData];
    }
    
    *width = CGImageGetWidth(image.CGImage);
    *height = CGImageGetHeight(image.CGImage);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    void *imageData = malloc( *height * *width * 4 );
    CGContextRef context = CGBitmapContextCreate( imageData, *width, *height, 8, 4 * *width, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big );
    CGColorSpaceRelease( colorSpace );
    CGContextClearRect( context, CGRectMake( 0, 0, *width, *height ) );
    CGContextTranslateCTM( context, 0, *height - *height );
    CGContextDrawImage( context, CGRectMake( 0, 0, *width, *height ), image.CGImage );
	
    CGContextRelease(context);
	return (char *)imageData;
};


#endif
