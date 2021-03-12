//
//  UserStorage.swift
//  FirstCourseFinalTask
//
//  Created by Dmitry Semenovich on 12.03.21.
//

import Foundation
import FirstCourseFinalTaskChecker

struct User : UserProtocol
{
    init(identifier: Identifier, userName: String, fullname: String, url: URL?,
         followsNum: Int, followedByNum: Int, currentFollows: Bool, currentFollowedBy: Bool, follow: Set<GenericIdentifier<UserProtocol>>, followBy: Set<GenericIdentifier<UserProtocol>>)
    {
        id = identifier
        username = userName
        fullName = fullname
        avatarURL = url
        followsCount = followsNum
        followedByCount = followedByNum
        currentUserFollowsThisUser = currentFollows
        currentUserIsFollowedByThisUser = currentFollowedBy
        follows = follow
        followedBy = followBy
    }
    
    var id: Identifier
    
    var username: String
    
    var fullName: String
    
    var avatarURL: URL?
    
    var currentUserFollowsThisUser: Bool
    
    var currentUserIsFollowedByThisUser: Bool
    
    var followsCount: Int
    
    var followedByCount: Int
    
    var follows : Set<GenericIdentifier<UserProtocol>>
    
    var followedBy : Set<GenericIdentifier<UserProtocol>>
}

class UsersStorage : UsersStorageProtocol
{
    var _usersStorage = Array<User>()
    var _currentUser : User
    
    required init?(users: [UserInitialData], followers: [(GenericIdentifier<UserProtocol>, GenericIdentifier<UserProtocol>)], currentUserID: GenericIdentifier<UserProtocol>)
    {
        var follows : Dictionary = [GenericIdentifier<UserProtocol>: Set<GenericIdentifier<UserProtocol>>]()
        
        var followedBy : Dictionary = [GenericIdentifier<UserProtocol> : Set<GenericIdentifier<UserProtocol>>]()
        
        for f in followers
        {
            let idFollows = f.0
            let idFollowedBy = f.1
            
            var arrFollows = follows[idFollows]
            arrFollows?.insert(idFollowedBy)
            follows[idFollows] = arrFollows
            
            var arrFollowedBy = followedBy[idFollowedBy]
            arrFollowedBy?.insert(idFollows)
            followedBy[idFollowedBy] = arrFollowedBy
        }
        
        for u in users
        {
            var isFollows = false
            var isFollowedBy = false
            
            if(((follows[currentUserID]?.contains(u.id))) != nil)
            {
                isFollows = true
            }
            
            if((follows[u.id]?.contains(currentUserID)) != nil)
            {
                isFollowedBy = true
            }
            
            let user = User(identifier: u.id, userName: u.username, fullname: u.fullName, url: u.avatarURL, followsNum: (follows[u.id]?.count)!, followedByNum: followedBy[u.id]!.count, currentFollows: isFollows, currentFollowedBy: isFollowedBy, follow: follows[u.id]!, followBy: followedBy[u.id]!)
                
            _usersStorage.append(user)
        }
        
        count = _usersStorage.count
        
        var isCorrectInit = false
        
        for u in _usersStorage
        {
            if(u.id == currentUserID)
            {
                _currentUser = u
                isCorrectInit = true
            }
        }
        
        if(!isCorrectInit)
        {
            return nil
        }
    }
    
    var count: Int
    
    func currentUser() -> UserProtocol {
        return _currentUser
    }
    
    func user(with userID: GenericIdentifier<UserProtocol>) -> UserProtocol? {
        
        var user : UserProtocol?
        
        for u in _usersStorage
        {
            if(u.id == userID)
            {
                user = u
            }
        }
        
        return user ?? nil
    }
    
    func findUsers(by searchString: String) -> [UserProtocol] {
        
        var usersArray : [UserProtocol]
        
        for u in _usersStorage
        {
            if(u.username.contains(searchString) || u.fullName.contains(searchString))
            {
                usersArray.append(u)
            }
        }
        
        return usersArray
    }
    
    func follow(_ userIDToFollow: GenericIdentifier<UserProtocol>) -> Bool {
        
        let userToFollow = user(with: userIDToFollow)
        
        if(userToFollow != nil)
        {
            _currentUser.follows.insert(userIDToFollow)
            
            return true
        }
        
        return false
    }
    
    func isFollow(_ userIDToFollow: GenericIdentifier<UserProtocol>, currentUser: User) -> Bool
    {
        var isFollow = false
        
        if(currentUser.followedBy.contains(userIDToFollow))
        {
            isFollow = true
        }
        
        return isFollow
    }
    
    func isFollowedBy(_ userIDToFollow: GenericIdentifier<UserProtocol>, currentUser: User) -> Bool
    {
        var isFollowedBy = false
        
        if(currentUser.follows.contains(userIDToFollow))
        {
            isFollowedBy = true
        }
        
        return isFollowedBy
    }
    
    func unfollow(_ userIDToUnfollow: GenericIdentifier<UserProtocol>) -> Bool {
        let userToUnfollow = user(with: userIDToUnfollow)
        
        if(userToUnfollow != nil)
        {
            let idx = _currentUser.follows.firstIndex(of: userIDToUnfollow)!
            _currentUser.follows.remove(at: idx)
        
            return true
        }
        
        return false
    }
    
    func usersFollowingUser(with userID: GenericIdentifier<UserProtocol>) -> [UserProtocol]? {
        
        let currUser = user(with: userID)
        
        var followArr : [UserProtocol]?
        
        for u in _usersStorage
        {
            if(isFollow(u.id, currentUser: currUser as! User))
            {
                followArr?.append(u)
            }
        }
        
        return followArr
    }
    
    func usersFollowedByUser(with userID: GenericIdentifier<UserProtocol>) -> [UserProtocol]? {
        let currUser = user(with: userID)
        
        var followedByArr : [UserProtocol]?
        
        for u in _usersStorage
        {
            if(isFollowedBy(u.id, currentUser: currUser as! User))
            {
                followedByArr?.append(u)
            }
        }
        
        return followedByArr
    }
}
