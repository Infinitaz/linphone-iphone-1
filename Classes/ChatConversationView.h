/*
 * Copyright (c) 2010-2020 Belledonne Communications SARL.
 *
 * This file is part of linphone-iphone 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#import <UIKit/UIKit.h>
#import <QuickLook/QLPreviewItem.h>
#import <QuickLook/QLPreviewController.h>

#import "UIToggleButton.h"
#import "UICompositeView.h"
#import "ChatConversationTableView.h"
#import "ImagePickerView.h"
#import "OrderedDictionary.h"
#import "UIRoundedImageView.h"
#import "UIBackToCallButton.h"
#import "Utils/HPGrowingTextView/HPGrowingTextView.h"
#import "UIImageViewDeletable.h"
#import "UIConfirmationDialog.h"
#import "UIInterfaceStyleButton.h"
#import "linphoneapp-Swift.h"
#import "UIChatReplyBubbleView.h"
#include "linphone/linphonecore.h"


//Quicklook Preview Item
@interface PreviewItem : NSObject <QLPreviewItem>
@property(readonly, nonatomic) NSURL    *previewItemURL;
@property(readonly, nonatomic) NSString *previewItemTitle;
@end

//QuickLook Datasource for rending PDF docs
@interface FileDataSource : NSObject <QLPreviewControllerDataSource>
@property NSMutableArray<NSURL*> *files;
@end

@interface ChatConversationView
	: TPMultiLayoutViewController <HPGrowingTextViewDelegate, UICompositeViewDelegate, ImagePickerDelegate, ChatConversationDelegate,
                        UIDocumentInteractionControllerDelegate, UISearchBarDelegate, UIImageViewDeletableDelegate,QLPreviewControllerDelegate, UICollectionViewDataSource,UICollectionViewDelegate,UIDocumentMenuDelegate,UIDocumentPickerDelegate,UITableViewDataSource, UITableViewDelegate> {
	OrderedDictionary *imageQualities;
	BOOL scrollOnGrowingEnabled;
	BOOL composingVisible;
    UIConfirmationDialog *securityDialog;
    UIRefreshControl *refreshControl;
	BOOL isOneToOne;
}

@property(nonatomic) LinphoneChatRoom *chatRoom;
@property(nonatomic) LinphoneChatRoomCbs *chatRoomCbs;
@property(nonatomic) Boolean markAsRead;
@property(nonatomic) const char *peerAddress;

@property (strong, nonatomic) FileDataSource *FileDataSource;

@property(weak, nonatomic) IBOutlet UIButton *backButton;
@property(nonatomic, strong) IBOutlet ChatConversationTableView *tableController;
@property(weak, nonatomic) IBOutlet HPGrowingTextView *messageField;
@property(weak, nonatomic) IBOutlet UIView *topBar;
@property(nonatomic, strong) IBOutlet UIButton *sendButton;
@property(nonatomic, strong) IBOutlet UILabel *addressLabel;
@property(nonatomic, strong) IBOutlet UIView *chatView;
@property(nonatomic, strong) IBOutlet UIView *messageView;
@property(nonatomic, strong) IBOutlet UITapGestureRecognizer *listTapGestureRecognizer;
@property(nonatomic, strong) IBOutlet UISwipeGestureRecognizer *listSwipeGestureRecognizer;
@property(strong, nonatomic) IBOutlet UILabel *composeLabel;
@property(strong, nonatomic) IBOutlet UIView *composeIndicatorView;
@property(nonatomic, strong) IBOutlet UIButton *pictureButton;
@property(weak, nonatomic) IBOutlet UIButton *callButton;
@property(weak, nonatomic) IBOutlet UIBackToCallButton *backToCallButton;
@property (weak, nonatomic) IBOutlet UIButton *infoButton;
@property (weak, nonatomic) IBOutlet UILabel *particpantsLabel;
@property NSMutableArray <NSNumber *> *qualitySettingsArray;
@property (weak, nonatomic) IBOutlet UICollectionView *imagesCollectionView;
@property (weak, nonatomic) IBOutlet UIView *imagesView;
@property (weak, nonatomic) IBOutlet UIButton *encryptedButton;
@property (weak, nonatomic) IBOutlet UIInterfaceStyleButton *toggleSelectionButton;
@property FileContext *fileContext;
@property (weak, nonatomic) IBOutlet UITableView *popupMenu;
@property (weak, nonatomic) IBOutlet UIInterfaceStyleButton *toggleMenuButton;
@property (weak, nonatomic) IBOutlet UIImageView *ephemeralndicator;


// Voice recording
@property (strong, nonatomic) IBOutlet UIView *vrView;
@property (weak, nonatomic) IBOutlet UIView *vrInnerView;
@property (weak, nonatomic) IBOutlet UIButton *vrDeleteButton;
@property (weak, nonatomic) IBOutlet UIButton *vrPlayButton;
@property (weak, nonatomic) IBOutlet UIImageView *vrWave;
@property (weak, nonatomic) IBOutlet UIView *vrWaveMask;
@property (weak, nonatomic) IBOutlet UIView *vrWaveMaskPlayer;
@property (weak, nonatomic) IBOutlet UILabel *vrDurationLabel;
@property NSTimer *vrRecordTimer;
@property NSTimer *vrPlayerTimer;
@property (weak, nonatomic) IBOutlet UIButton *toggleRecord;
@property BOOL isVoiceRecording;
@property BOOL isPendingVoiceRecord;
@property BOOL isPlayingVoiceRecording;
@property LinphoneRecorder *voiceRecorder;
@property LinphonePlayer *sharedVoicePlayer;
@property BOOL showVoiceRecorderView;
@property BOOL preservePendingActions;

// Reply
@property (weak, nonatomic) IBOutlet UIView *replyView;
@property BOOL showReplyView;
@property UIChatReplyBubbleView *replyBubble;

// Forward
@property LinphoneChatMessage *pendingForwardMessage;


+ (void)markAsRead:(LinphoneChatRoom *)chatRoom;
+ (void)autoDownload:(LinphoneChatMessage *)message;
+(NSString *)getKeyFromFileType:(NSString *)fileType fileName:(NSString *)name;
+ (NSURL *)getFileUrl:(NSString *)name;
+ (void)writeFileInImagesDirectory:(NSData *)data name:(NSString *)name;
+ (NSData *)getFileData:(NSString *)name;
+ (void)writeMediaToGallery:(NSString *)name fileType:(NSString *)fileType;
+(UIImage *)getBasicImage;
+(UIImage*)drawText:(NSString*)text image:(UIImage *)image textSize:(CGFloat)textSize;
+(BOOL) isBasicChatRoom:(LinphoneChatRoom *)room;

- (void)configureForRoom:(BOOL)editing;
- (IBAction)onBackClick:(id)event;
- (IBAction)onEditClick:(id)event;
- (IBAction)onMessageChange:(id)sender;
- (IBAction)onSendClick:(id)event;
- (IBAction)onPictureClick:(id)event;
- (IBAction)onListTap:(id)sender;
- (IBAction)onCallClick:(id)sender;
- (IBAction)onDeleteClick:(id)sender;
- (IBAction)onEditionChangeClick:(id)sender;
- (IBAction)onEncryptedDevicesClick:(id)sender;
- (void)update;
- (void)openFileWithURL:(NSURL *)url;
- (void)openFileWithURLs:(NSMutableArray<NSURL *>*)urls index:(NSInteger)currentIndex;
- (void)clearMessageView;
- (void)configureMessageField;

- (void)showFileDownloadError;
- (NSURL *)getICloudFileUrl:(NSString *)name;
- (void)removeCallBacks;

-(void) startSharedPlayer:(const char *)path;
-(void) stopSharedPlayer;
-(BOOL) sharedPlayedIsPlaying:(const char *)path;

-(void) initiateReplyViewForMessage:(LinphoneChatMessage *)message;

@end
