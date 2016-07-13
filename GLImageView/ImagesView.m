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
@property(atomic, assign) CGLayerRef drawLayer;

@property(nonatomic, retain) UIImage *img;

@end
typedef void (^render_block_t)(CGContextRef);

@implementation ImagesView

- (instancetype) initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
    }
    return self;
}

- (CGLayerRef)rendLayer:(render_block_t) block {
    UIGraphicsBeginImageContext(CGSizeMake(100, 100));
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGLayerRef cgLayer = CGLayerCreateWithContext(context, CGSizeMake(100, 100), nil);
    block(CGLayerGetContext(cgLayer));
    UIGraphicsEndImageContext();
    return cgLayer;
}

- (void)update {
    if (self.drawLayer) {
        return;
    }
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        typedef void (^render_block_image)(CGContextRef, NSString *);
        render_block_image block = ^(CGContextRef c, NSString *name) {CGContextSetAllowsAntialiasing(c, YES);
            CGContextSetInterpolationQuality(c, kCGInterpolationHigh);
            CGContextAddEllipseInRect(c, CGRectMake(0, 0, 100, 100));
            CGContextClip(c);
            CGImageRef img = [[UIImage imageNamed:name] CGImage];
            CGContextDrawImage(c, CGRectMake(0, 0, 100, 100), img);
            
            CGContextSetRGBStrokeColor(c,1,1,1,1.0);
            CGContextSetLineWidth(c, 8.0);
            CGContextAddArc(c, 50, 50, 48, 0, 2*3.14159, 0);
            CGContextDrawPath(c, kCGPathStroke);
        };
        
        //
        int i = 1;
        CGLayerRef cgLayer = [self rendLayer:^(CGContextRef c) {
            block(c, [NSString stringWithFormat:@"%d", i]);
        }];
        
        //
        int j = 2;
        CGLayerRef cgLayer1 = [self rendLayer:^(CGContextRef c) {
            block(c, [NSString stringWithFormat:@"%d", j]);
        }];
        
        //
        int k = 2;
        CGLayerRef cgLayer2 = [self rendLayer:^(CGContextRef c) {
            block(c, [NSString stringWithFormat:@"%d", k]);
        }];
        
        self.drawLayer = [self rendLayer:^(CGContextRef c3) {
            CGContextSetAllowsAntialiasing(c3, YES);
            CGContextDrawLayerAtPoint(c3, CGPointMake(50, 0), cgLayer);
            CGContextDrawLayerAtPoint(c3, CGPointMake(100, 50), cgLayer1);
            CGContextDrawLayerAtPoint(c3, CGPointMake(0, 50), cgLayer2);
        }];
        
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
        return;
    }
    
}


@end
