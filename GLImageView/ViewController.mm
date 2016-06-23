//
//  ViewController.m
//  GLImageView
//
//  Created by 彭浩 on 16/5/5.
//  Copyright © 2016年 彭浩. All rights reserved.
//

#import "ViewController.h"
#import "GLView.h"

@interface ViewController ()
@property(nonatomic, strong)UITableView *tableView;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.tableView = [[UITableView alloc] initWithFrame:self.view.frame style:UITableViewStylePlain];
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
    
    
    // Do any additional setup after loading the view, typically from a nib.
//    GLView *glView = [[GLView alloc] initWithFrame: CGRectMake(0, 0, 320, 320)];
//    [glView addImage:@"share_camera@2x" frame:CGRectMake(20, 100, 160, 160)];
//    [glView addImage:@"share_case@2x" frame:CGRectMake(100, 100, 160, 160)];
    [self.view addSubview:self.tableView];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 1000;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 50;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell * cell = [tableView dequeueReusableCellWithIdentifier:@"UITableViewCell"];
//    UIImageView *imageView = nil;
//    if (!cell) {
//        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"UITableViewCell"];
//        imageView = [[UIImageView alloc] initWithFrame: CGRectMake(5, 5, 40, 40)];
//        imageView.tag = 999;
//        [cell addSubview:imageView];
//        imageView.layer.cornerRadius = 20;
//        imageView.layer.masksToBounds = true;
//    } else {
//        imageView = [cell viewWithTag:999];
//    }
//    int i = indexPath.row%43;
//    if (i == 18) {
//        i = 19;
//    }
//    imageView.image = [UIImage imageNamed:[NSString stringWithFormat:@"%d.jpg", i]];
    
    
    GLView *glView = nil;
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"UITableViewCell"];
        glView = [[GLView alloc] initWithFrame: CGRectMake(0, 0, 50, 50)];
        glView.tag = 999;
        [cell addSubview:glView];
    } else {
        glView = [cell viewWithTag:999];
    }
    [glView removeAllImages];
    int i = indexPath.row%43;
    if (i == 18) {
        i = 19;
    }
    [glView addImage:[NSString stringWithFormat:@"%d.jpg", i] frame:CGRectMake(5, 5, 40, 40)];
    
    
    return cell;
}

@end
