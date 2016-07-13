//
//  ViewController.m
//  GLImageView
//
//  Created by 彭浩 on 16/5/5.
//  Copyright © 2016年 彭浩. All rights reserved.
//

#import "ViewController.h"
#import "GLView.h"
#import "ImagesView.h"

@interface ViewController () {
    char t[10];
}
@property(nonatomic, strong)UITableView *tableView;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    memset(t, 0, 100);
    
    self.tableView = [[UITableView alloc] initWithFrame:self.view.bounds style:UITableViewStylePlain];
    self.tableView.delegate = self;
    self.tableView.dataSource = self;
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
    return 100;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell * cell = [tableView dequeueReusableCellWithIdentifier:@"UITableViewCell"];
    
    int i = indexPath.row%43;
    if (i == 18) {
        i = 19;
    }

    ImagesView *view = nil;
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"UITableViewCell"];
        view = [[ImagesView alloc] initWithFrame:CGRectMake(0, 0, 100, 100)];
        view.backgroundColor = [UIColor whiteColor];
        
        [cell addSubview:view];
    } else {
    }
    [view update];
    
    
    
    
//    GLView *glView = nil;
//    if (!cell) {
//        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"UITableViewCell"];
//        glView = [[GLView alloc] initWithFrame: CGRectMake(0, 0, 300, 300)];
//        glView.tag = 999;
//        [cell addSubview:glView];
//    } else {
//        glView = [cell viewWithTag:999];
//    }
//    [glView removeAllImages];
//    [glView addImage:[NSString stringWithFormat:@"%d.jpg", i] frame:CGRectMake(5, 5, 290, 290)];
    
    return cell;
}

@end
