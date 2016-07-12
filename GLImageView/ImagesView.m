//
//  ImagesView.m
//  GLImageView
//
//  Created by 彭浩 on 16/7/12.
//  Copyright © 2016年 彭浩. All rights reserved.
//

#import "ImagesView.h"
#import <QuartzCore/QuartzCore.h>
#import <CoreGraphics/CoreGraphics.h>

@interface ImagesView ()
@property(nonatomic, assign) CGLayerRef drawLayer;

@end

@implementation ImagesView


- (instancetype) initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
    }
    return self;
}

- (void)update {
    
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        
        //
        UIGraphicsBeginImageContext(CGSizeMake(100, 100));
        CGContextRef context = UIGraphicsGetCurrentContext();
        CGContextSetAllowsAntialiasing(context, YES);
        CGLayerRef cgLayer = CGLayerCreateWithContext(context, CGSizeMake(100, 100), nil);
        CGContextRef c = CGLayerGetContext(cgLayer);
        CGContextSetInterpolationQuality(c, kCGInterpolationHigh);
        CGContextAddEllipseInRect(c, CGRectMake(0, 0, 100, 100));
        CGContextClip(c);
        int i = 1;
        CGImageRef img = [[UIImage imageNamed:[NSString stringWithFormat:@"%d", i]] CGImage];
        CGContextDrawImage(c, CGRectMake(0, 0, 100, 100), img);
        
        CGContextSetRGBStrokeColor(c,1,1,1,1.0);
        CGContextSetLineWidth(c, 8.0);
        CGContextAddArc(c, 50, 50, 48, 0, 2*3.14159, 0);
        CGContextDrawPath(c, kCGPathStroke);
        
        UIGraphicsEndImageContext();
        
        //
        
        
        UIGraphicsBeginImageContext(CGSizeMake(100, 100));
        context = UIGraphicsGetCurrentContext();
        CGContextSetAllowsAntialiasing(context, YES);
        CGLayerRef cgLayer1 = CGLayerCreateWithContext(context, CGSizeMake(100, 100), nil);
        CGContextRef c1 = CGLayerGetContext(cgLayer1);
        CGContextSetInterpolationQuality(c1, kCGInterpolationHigh);
        CGContextAddEllipseInRect(c1, CGRectMake(0, 0, 100, 100));
        CGContextClip(c1);
        
        int j = 2;
        CGImageRef img1 = [[UIImage imageNamed:[NSString stringWithFormat:@"%d", j]] CGImage];
        CGContextDrawImage(c1, CGRectMake(0, 0, 100, 100), img1);
        
        CGContextSetRGBStrokeColor(c1,1,1,1,1.0);
        CGContextSetLineWidth(c1, 8.0);
        CGContextAddArc(c1, 50, 50, 48, 0, 2*3.14159, 0);
        CGContextDrawPath(c1, kCGPathStroke);
        
        UIGraphicsEndImageContext();
        
        //
        
        UIGraphicsBeginImageContext(CGSizeMake(100, 100));
        
        context = UIGraphicsGetCurrentContext();
        CGContextSetAllowsAntialiasing(context, YES);
        CGLayerRef cgLayer2 = CGLayerCreateWithContext(context, CGSizeMake(100, 100), nil);
        CGContextRef c2 = CGLayerGetContext(cgLayer2);
        CGContextSetInterpolationQuality(c2, kCGInterpolationHigh);
        CGContextAddEllipseInRect(c2, CGRectMake(0, 0, 100, 100));
        CGContextClip(c2);
        
        int k = 3;
        CGImageRef img2 = [[UIImage imageNamed:[NSString stringWithFormat:@"%d", k]] CGImage];
        CGContextDrawImage(c2, CGRectMake(0, 0, 100, 100), img2);
        
        CGContextSetRGBStrokeColor(c2,1,1,1,1.0);
        CGContextSetLineWidth(c2, 8.0);
        CGContextAddArc(c2, 50, 50, 48, 0, 2*3.14159, 0);
        CGContextDrawPath(c2, kCGPathStroke);
        
        UIGraphicsEndImageContext();
        
        
        UIGraphicsBeginImageContext(CGSizeMake(100, 100));
        context = UIGraphicsGetCurrentContext();
        CGContextSetAllowsAntialiasing(context, YES);
        CGLayerRef cgLayer3 = CGLayerCreateWithContext(context, CGSizeMake(300, 300), nil);
        CGContextRef c3 = CGLayerGetContext(cgLayer3);
        CGContextDrawLayerAtPoint(c3, CGPointMake(50, 0), cgLayer);
        CGContextDrawLayerAtPoint(c3, CGPointMake(100, 50), cgLayer1);
        CGContextDrawLayerAtPoint(c3, CGPointMake(0, 50), cgLayer2);
        
        UIGraphicsEndImageContext();
        
        self.drawLayer = cgLayer3;
        dispatch_async(dispatch_get_main_queue(), ^{
            [self setNeedsDisplay];
        });
    });
}

- (void)drawRect:(CGRect)rect {
    if (self.drawLayer) {
        
        CGContextRef context = UIGraphicsGetCurrentContext();
        CGContextSetAllowsAntialiasing(context, YES);
        CGContextDrawLayerAtPoint(context, CGPointZero, self.drawLayer);
        self.drawLayer = nil;
        return;
    }
    
}


@end
