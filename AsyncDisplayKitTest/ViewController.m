//
//  ViewController.m
//  AsyncDisplayKitTest
//
//  Created by janezhuang on 2023/9/14.
//  Copyright © 2023 Facebook. All rights reserved.
//

#import "ViewController.h"
#import "ASDisplayNode.h"
#import "BlurbNode.h"
#import "KittenNode.h"

static const NSInteger kLitterSize = 30;

@interface ViewController () <ASTableViewDataSource, ASTableViewDelegate> {
    ASTableView *_tableView;

    // array of boxed CGSizes corresponding to placekitten kittens
    NSArray *_kittenDataSource;
}

@property (nonatomic) ASDisplayNode *node;

@end

@implementation ViewController

#pragma mark -
#pragma mark UIViewController.

- (void)viewDidLoad {
    [super viewDidLoad];

    //    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
    //        ASDisplayNode *node4 = [[ASDisplayNode alloc] init];
    //        self.node = [[ASDisplayNode alloc] init];
    //        self.node.frame = CGRectMake(60, 60, 240, 240);
    //        self.node.backgroundColor = UIColor.lightGrayColor;
    //
    //        ASDisplayNode *node2 = [[ASDisplayNode alloc] init];
    //        node2.frame = CGRectMake(0, 0, 120, 120);
    //        node2.backgroundColor = UIColor.redColor;
    //        node2.layerBacked = YES;
    //        [self.node addSubnode:node2];
    //
    //        ASDisplayNode *node3 = [[ASDisplayNode alloc] init];
    //        node3.frame = CGRectMake(120, 0, 120, 120);
    //        node3.backgroundColor = UIColor.blueColor;
    //        node3.layerBacked = YES;
    //        [self.node addSubnode:node3];
    //
    //        [node2 setNeedsLayout];
    //
    //        dispatch_async(dispatch_get_main_queue(), ^{
    //            [self.view addSubview:self.node.view];
    //        });
    //    });
    //
    //    return;

    _tableView = [[ASTableView alloc] initWithFrame:CGRectZero style:UITableViewStylePlain];
    _tableView.separatorStyle = UITableViewCellSeparatorStyleNone; // KittenNode has its own separator
    _tableView.asyncDataSource = self;
    _tableView.asyncDelegate = self;

    // populate our "data source" with some random kittens
    NSMutableArray *kittenDataSource = [NSMutableArray arrayWithCapacity:kLitterSize];
    for (NSInteger i = 0; i < kLitterSize; i++) {
        u_int32_t deltaX = arc4random_uniform(10) - 5;
        u_int32_t deltaY = arc4random_uniform(10) - 5;
        CGSize size = CGSizeMake(350 + 2 * deltaX, 350 + 4 * deltaY);

        [kittenDataSource addObject:[NSValue valueWithCGSize:size]];
    }
    _kittenDataSource = kittenDataSource;

    [self.view addSubview:_tableView];
}

- (void)viewWillLayoutSubviews {
    _tableView.frame = self.view.bounds;
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

#pragma mark -
#pragma mark Kittens.

- (ASCellNode *)tableView:(ASTableView *)tableView nodeForRowAtIndexPath:(NSIndexPath *)indexPath {
    // special-case the first row
    if (indexPath.section == 0 && indexPath.row == 0) {
        BlurbNode *node = [[BlurbNode alloc] init];
        return node;
    }

    NSValue *size = _kittenDataSource[indexPath.row - 1];
    KittenNode *node = [[KittenNode alloc] initWithKittenOfSize:size.CGSizeValue];
    return node;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    // blurb node + kLitterSize kitties
    return 1 + _kittenDataSource.count;
}

- (BOOL)tableView:(UITableView *)tableView shouldHighlightRowAtIndexPath:(NSIndexPath *)indexPath {
    // disable row selection
    return NO;
}

@end
